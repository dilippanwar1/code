## Inspect various kubernetes internal representation.

- Start kubernetes cluster.
- Build and push images under images/ folder, follow instructions in Dockerfile.
- Create pod:
  ```
  $ kubectl.sh create -f k8s-inspect-pod.json
  ```
- ssh into the minion pod is running, and check the logs 'docker logs ${id}'
- Delete pod:
  ```
  $ kubectl.sh get pods k8s-inspect-pod
  ```
