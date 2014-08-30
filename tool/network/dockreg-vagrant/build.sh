#!/bin/sh

echo "Build Docker image with HTTP server and dockreg"
cd /vagrant
docker build -t local/dockreg .

echo "Download run etcd container"
docker run -p 4001:4001 -p 7001:7001 -d --name etcd \
       coreos/etcd -name $1 -peer-addr $2:7001 -addr $2:4001 $3
