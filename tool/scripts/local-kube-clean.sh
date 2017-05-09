#!/bin/bash

echo "removing log files under /tmp"
sudo rm -rf /tmp/kube-apiserver.log \
     /tmp/kube-controller-manager.log \
     /tmp/kubelet.log \
     /tmp/kube-proxy.log \
     /tmp/kube-scheduler.log \
     /tmp/kube-serviceaccount.key

echo "removing /var/lib/kubelet"
for mountpt in `mount | grep kubelet | awk '{print $3}'`; do
  echo "  umounting ${mountpt}"
  sudo umount $mountpt
done
sudo rm -rf /var/lib/kubelet

echo "removing /var/run/kubernetes"
sudo rm -rf /var/run/kubernetes
