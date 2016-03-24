### Kubernetes v1.2 deployment

#### Deployment updates

- Create a deployment

`kubectl create -f deployment.yaml --record`

- Update the deployment (env value change)

`kubectl apply -f updated-deployment.yaml --record`

We'll be able to see changes applied to the deployment. However, running the same
sequence of instructions with replication controller doesn't take any effect.
