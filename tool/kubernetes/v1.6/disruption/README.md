### Kubernetes v1.6 pod disruption budget

- Create a deployment

```sh
$ kubectl run --image nginx --replicas=3 nginx

$ kubectl get pods -o wide
NAME                    READY     STATUS    RESTARTS   AGE       IP           NODE
nginx-348975970-2q84t   1/1       Running   0          31s       172.17.0.4   127.0.0.1
nginx-348975970-9xbdb   1/1       Running   0          31s       172.17.0.2   127.0.0.1
nginx-348975970-w8t8t   1/1       Running   0          31s       172.17.0.3   127.0.0.1
```

- Create disruption budget

```sh
$ kubectl create -f budget.yaml
```

- Evict one pod, then evict two pods to see result

```sh
curl -v -H 'Content-type: application/json' http://127.0.0.1:8080/api/v1/namespaces/default/pods/nginx-348975970-2q84t/eviction -d @eviction.json
```
