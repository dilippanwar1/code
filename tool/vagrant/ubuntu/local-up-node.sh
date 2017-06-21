#!/bin/bash
#
# Used in conjunction with kubernetes ./hack/local-up-cluster.sh
#
# Must add one line to local-up-cluster.sh to create certs that will also
# certify vagrant private IP, i.e, append "192.168.33.1" to shell function
# kube::util::create_serving_certkey


# scp files to given instance, e.g.
#  scp-to-instance "root:password@43.254.54.58" "file1 file2" "~/destdir"
#
# Input:
#   $1 ssh info, e.g. root:password@43.254.54.58
#   $2 files to copy, separate with space
#   $3 destination directory on remote machine
#   $4 Optional timeout
function scp-to-instance-expect {
  IFS=':@' read -ra ssh_info <<< "${1}"
  timeout=${4:-"-1"}
  expect <<EOF
set timeout ${timeout}
spawn sudo scp -r ${SSH_OPTS} ${2} ${ssh_info[0]}@${ssh_info[2]}:${3}
expect {
  "*?assword:" {
    send -- "${ssh_info[1]}\r"
    exp_continue
  }
  "?ommand failed" {exit 1}
  "lost connection" { exit 1 }
  eof {}
}
EOF
}

function cleanup {
  vagrant ssh -c "sudo killall hyperkube && \
    sudo rm -rf /var/run/kubernetes &&
    sudo rm -rf /tmp/kubernetes &&
    sudo rm /tmp/kube-proxy.yaml"
  sudo rm -rf /tmp/kubernetes
}

cleanup

# Copy runtime information to node
sudo cp -r /var/run/kubernetes /tmp
sudo sed -i "s/localhost/192.168.33.1/g" /tmp/kubernetes/kubelet.kubeconfig
sudo sed -i "s/localhost/192.168.33.1/g" /tmp/kubernetes/kube-proxy.kubeconfig

scp-to-instance-expect "vagrant:vagrant@192.168.33.33" \
                       "$GOPATH/src/k8s.io/kubernetes/_output/local/bin/linux/amd64/hyperkube \
                       /tmp/kubernetes \
                       /tmp/kube-proxy.yaml" \
                       "/tmp"

vagrant ssh -c "sudo mv /tmp/kubernetes /var/run"

vagrant ssh -c "sudo /tmp/hyperkube kubelet \
  --v=3 \
  --chaos-chance=0.0 \
  --container-runtime=docker \
  --rkt-path= \
  --rkt-stage1-image= \
  --hostname-override=192.168.33.33 \
  --cloud-provider= \
  --cloud-config= \
  --address=127.0.0.1 \
  --require-kubeconfig \
  --kubeconfig /var/run/kubernetes/kubelet.kubeconfig \
  --feature-gates=AllAlpha=true \
  --cpu-cfs-quota=true \
  --enable-controller-attach-detach=true \
  --cgroups-per-qos=true \
  --cgroup-driver=cgroupfs \
  --keep-terminated-pod-volumes=true \
  --eviction-hard=memory.available\<100Mi \
  --eviction-soft= \
  --eviction-pressure-transition-period=1m \
  --pod-manifest-path=/var/run/kubernetes/static-pods \
  --cluster-dns=10.0.0.10 \
  --cluster-domain=cluster.local \
  --port=10250 > /tmp/kubelet.log 2>&1" &
KUBELET_PID=$!

vagrant ssh -c "sudo /tmp/hyperkube proxy \
  --config=/tmp/kube-proxy.yaml \
  --master=https://192.168.33.1:6443 \
  --v=3 >/tmp/kube-proxy.log 2>&1" &
PROXY_PID=$!

trap cleanup EXIT

  cat <<EOF


Joined 192.168.33.33 to local cluster. Press Ctrl-C to shut it down

Logs:
  /tmp/kubelet.log
  /tmp/kube-proxy.log
EOF

while true; do sleep 1; done
