#!/bin/bash

# Using () won't be able to pass environment var.
(
  REGISTRY_USERNAME="admin"
  REGISTRY_PASSWORD="admin_password"
  ENABLE_CAICLOUD_AUTH="false"
  ./subprocess_2.sh
)

echo "Done"
