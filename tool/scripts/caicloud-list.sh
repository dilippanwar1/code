#!/bin/bash

if [[ "${1:-}" == "prod" ]]; then
  echo "Listing caicloud prod rc, excluding mongo, redis and influxdb"
  kubectl get rc --kubeconfig=$HOME/.kube/config-prod-aliyun -o wide | grep -v "mongo\|redis\|influxdb"
else
  echo "Listing caicloud canary rc, excluding mongo, redis and influxdb"
  kubectl get rc --kubeconfig=$HOME/.kube/config-caicloud-canary -o wide | grep -v "mongo\|redis\|influxdb"
fi
