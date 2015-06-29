#!/bin/bash


# Assume we can login to deyuan.me
scp -r -oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null -oLogLevel=quiet \
    ./sleep_touch.sh deyuan@deyuan.me:~


# To run expect in backgroud, we append '&' to end of first line. Note we can't
# remove the 'expect eof' in expect script - removing that line is not run script
# in background, it will result the script not being ran.
expect <<EOF &
set timeout 360
spawn ssh -oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null -oLogLevel=quiet \
  deyuan@deyuan.me "./sleep_touch.sh"
expect eof
EOF


echo "It's here"
sleep 5
