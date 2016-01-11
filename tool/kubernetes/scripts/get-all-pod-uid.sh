#!/bin/bash

PODS=`kubectl get pods | awk '{if (NR!=1) print $1}'`

for pod in ${PODS}; do
  uid_value=`kubectl get pods $pod --template={{.metadata.uid}}`
  echo "${pod}", "${uid_value}"
done

echo "................"
PODS=`kubectl get pod --namespace=canary | awk '{if (NR!=1) print $1}'`

for pod in ${PODS}; do
  uid_value=`kubectl get pod $pod --template={{.metadata.uid}} --namespace=canary`
  echo "${pod}", "${uid_value}"
done

echo "................"
PODS=`kubectl get pod --namespace=kube-system | awk '{if (NR!=1) print $1}'`

for pod in ${PODS}; do
  uid_value=`kubectl get pod $pod --template={{.metadata.uid}} --namespace=kube-system`
  echo "${pod}", "${uid_value}"
done
