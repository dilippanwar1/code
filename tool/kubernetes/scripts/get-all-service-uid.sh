#!/bin/bash

SERVICES=`kubectl get service | awk '{if (NR!=1) print $1}'`

for service in ${SERVICES}; do
  uid_value=`kubectl get service $service --template={{.metadata.uid}}`
  uid_value_add_a="a"${uid_value}
  uid_remove_dash=${uid_value_add_a//-}
  uid_32bytes=${uid_remove_dash:0:32}
  echo "${service}", "${uid_32bytes}"
done

echo "................"
SERVICES=`kubectl get service --namespace=canary | awk '{if (NR!=1) print $1}'`

for service in ${SERVICES}; do
  uid_value=`kubectl get service $service --template={{.metadata.uid}} --namespace=canary`
  uid_value_add_a="a"${uid_value}
  uid_remove_dash=${uid_value_add_a//-}
  uid_32bytes=${uid_remove_dash:0:32}
  echo "${service}", "${uid_32bytes}"
done

echo "................"
SERVICES=`kubectl get service --namespace=kube-system | awk '{if (NR!=1) print $1}'`

for service in ${SERVICES}; do
  uid_value=`kubectl get service $service --template={{.metadata.uid}} --namespace=kube-system`
  uid_value_add_a="a"${uid_value}
  uid_remove_dash=${uid_value_add_a//-}
  uid_32bytes=${uid_remove_dash:0:32}
  echo "${service}", "${uid_32bytes}"
done
