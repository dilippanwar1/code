#!/bin/bash


# Find IP address of an interface
# http://unix.stackexchange.com/questions/8518/how-to-get-my-own-ip-address-and-save-it-to-a-variable-in-a-shell-script
ifconfig | grep -A 1 'eth0' | tail -1 | cut -d ':' -f 2 | cut -d ' ' -f 1

IP_ADDRESS=wlan0
if [[ ! ${IP_ADDRESS} =~ ^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$ ]]; then
  echo `ifconfig | grep -A 1 ${IP_ADDRESS} | tail -1 | cut -d ':' -f 2 | cut -d ' ' -f 1`
fi

# ssh to given node and execute command, e.g.
#   ssh-to-instance "root:password@43.254.54.58" "touch abc && mkdir def"
# The function doesn't use expect, just plan ssh.
#
# Input:
#   $1 ssh info, e.g. root:password@43.254.54.58
#   $2 Command string
function ssh-to-instance {
  IFS=':@' read -ra ssh_info <<< "${1}"
  ssh -t ${SSH_OPTS} ${ssh_info[0]}@${ssh_info[2]} ${2}
}


SSH_OPTS="-oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null -oLogLevel=quiet"
KUBELET_ADDRESS=eth1

kubelet_ip_address=`ssh-to-instance "vagrant:vagrant@192.168.205.11" \
"ifconfig | grep -A 1 ${KUBELET_ADDRESS} | tail -1 | cut -d ':' -f 2 | cut -d ' ' -f 1" | tr -d " \t\n\r"`

echo ${kubelet_ip_address} > /tmp/kubekube


MASTER_SSH_INFO=${MASTER_SSH_INFO:-"vagrant:vagrant@192.168.205.10"}
if [[ "${MASTER_SSH_INFO}" =~ "vagrant" ]]; then
  echo "........."
fi
