#!/bin/bash
# Shell function Examples

# Function name can contain ":", which is a good way to
# enforce namespace in shell script.
kube::game::start() {
  echo "Come on"
}

kube::game::stop() {
  echo "Game over"
}

kube::game::start
kube::game::stop
