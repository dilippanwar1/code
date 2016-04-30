#!/bin/bash

to_replace=(\
  "quota_cpu" "quota_mem" "get_quota" "limit_type" \
              "limit_max_cpu" "limit_max_mem" "default_cpu_request" "default_mem_request" \
              "default_cpu_limit" "default_mem_limit" "partition_name" "application_name" \
              "get_quota" "app_type" "exposed_ports")
replace_to=(\
  "quotaCpu" "quotaMem" "getQuota" "limitType"  \
             "limitMaxCpu" "limitMaxMem" "defaultCpuRequest" "defaultMemRequest" \
             "defaultCpuLimit" "defaultMemLimit" "partitionName" "applicationName" \
             "getQuota" "appType" "exposedPorts")

# Replace string in a folder, recursively.
for i in `seq 0 ${#to_replace[@]}`; do
  grep -rl ${to_replace[$i]} . | xargs sed -i 's/${to_replace[$i]}/${replace_to[$i]/g'
done
