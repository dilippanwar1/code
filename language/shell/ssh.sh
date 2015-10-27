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

scp-to-node "array.sh bool.sh" "root@43.254.54.58" "~" "xxxxxxx"
