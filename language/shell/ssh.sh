#!/bin/bash

ssh-add -L > /dev/null 2>&1
# Could not open a connection to authentication agent (ssh-agent),
# try creating one.
if [[ "$?" == "2" ]]; then
  eval "$(ssh-agent)" > /dev/null
  trap-add "kill ${SSH_AGENT_PID}" EXIT
fi

ssh-add -L > /dev/null 2>&1
# The agent has no identities, try adding one of the default identities,
# with or without pass phrase.
if [[ "$?" == "1" ]]; then
  ssh-add || true
fi

# Expect at least one identity to be available.
if ! ssh-add -L > /dev/null 2>&1; then
  echo "Could not find or add an SSH identity."
  echo "Please start ssh-agent, add your identity, and retry."
  exit 1
fi

function ssh-to-node {
  expect <<EOF
set timeout -1
spawn ssh -t ${SSH_OPTS} $1 $2
expect {
  "*?assword*" {
    send -- "${3}\r"
    exp_continue
  }
  eof {}
}
EOF
}

function scp-to-node {
  expect <<EOF
set timeout -1
spawn scp -r ${SSH_OPTS} $1 $2:$3
expect {
  "*?assword:" {
    send -- "${4}\r"
    exp_continue
  }
  eof {}
}
EOF
}


function scp-from-instance {
  IFS=':@' read -ra ssh_info <<< "${1}"
  expect <<EOF
set timeout -1
spawn scp -r ${SSH_OPTS} ${ssh_info[0]}@${ssh_info[2]}:${2} ${3}
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

# ssh to given node and execute command, e.g.
#   ssh-to-instance "root:password@43.254.54.58" "touch abc && mkdir def"
#
# Input:
#   $1 ssh info, e.g. root:password@43.254.54.58
#   $2 Command string
function ssh-to-instance {
  IFS=':@' read -ra ssh_info <<< "${1}"
  expect <<EOF
set timeout -1
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

ssh-to-instance "ubuntu:nopasswd@43.254.54.61" "\
touch abc && \
echo 'hahhah' > abc && \
echo 'xfe' >> abc"
