SSH_OPTS="-oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null -oLogLevel=ERROR"

# ssh to given node and execute command, e.g.
#   ssh-to-instance "root:password@43.254.54.58" "touch abc && mkdir def"
#
# Input:
#   $1 ssh info, e.g. root:password@43.254.54.58
#   $2 Command string
#   $3 Optional timeout
function ssh-to-instance-expect {
  IFS=':@' read -ra ssh_info <<< "${1}"
  timeout=${3:-"-1"}
  expect <<EOF
set timeout ${timeout}
spawn ssh -t ${SSH_OPTS} ${ssh_info[0]}@${ssh_info[2]} ${2}
expect {
  "*?assword*" {
    send -- "${ssh_info[1]}\r"
    exp_continue
  }
  "?ommand failed" {exit 1}
  "lost connection" { exit 1 }
  eof {}
}
EOF
}

arrary_c1="192.168.10.101 192.168.10.102 192.168.10.103 192.168.10.104 192.168.10.105 192.168.10.106 192.168.10.107 192.168.10.108 192.168.10.109 192.168.10.110 192.168.10.111 192.168.10.112"
arrary_c2="192.168.10.113 192.168.10.114 192.168.10.115 192.168.10.116 192.168.10.117 192.168.10.118 192.168.10.119 192.168.10.120 192.168.10.121 192.168.10.122 192.168.10.123 192.168.10.124"
arrary_c3="192.168.10.125 192.168.10.126 192.168.10.127 192.168.10.128 192.168.10.129 192.168.10.130 192.168.10.131 192.168.10.132 192.168.10.133 192.168.10.134 192.168.10.135 192.168.10.136"

arrary_00="192.168.10.101"
# for IP in $arrary_c3; do
#   ping -c 2 $IP;
# done

for IP in $arrary_c3; do
  ssh-to-instance-expect "root:password@$IP" "echo 'DNS1=114.114.114.114' >> /etc/sysconfig/network-scripts/ifcfg-eth0 && systemctl restart network"
done
