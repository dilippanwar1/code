## Kubernetes service external name (k8s v1.6)

#### Create external name service

```sh
$ kubectl create -f svc-external.yaml
service "caas" created
```

#### Check CNAME

```sh
$ host -t cname caas.default.svc.cluster.local 10.0.0.10
Using domain server:
Name: 10.0.0.10
Address: 10.0.0.10#53
Aliases:

caas.default.svc.cluster.local is an alias for caas.caicloud.
```
