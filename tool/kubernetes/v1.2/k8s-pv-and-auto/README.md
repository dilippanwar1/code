### Kubernetes 1.2 PV/PVC and auto-provisioning

#### PV/PVC

- Create a cloud disk and change the volume name field in pc-xxx.yaml

- Create a PV

```
$ kubectl create pv-gce.yaml --kubeconfig=$HOME/.kube/config-gce
$ kubectl get pv --kubeconfig=$HOME/.kube/config-gce
NAME      CAPACITY   ACCESSMODES   STATUS      CLAIM     REASON    AGE
pv0003    10Gi       RWO           Available                       19s
```

PV is created by kubernetes admin, and is almost immediately available (without acutally
check the status of the underline volume)

- Create a PVC

```
$ kubectl create -f pvc.yaml --kubeconfig=$HOME/.kube/config-gce
$ kubectl get pvc --kubeconfig=$HOME/.kube/config-gce
NAME      STATUS    VOLUME    CAPACITY   ACCESSMODES   AGE
myclaim   Bound     pv0003    10Gi       RWO           9s
```

Since PVC claims less resources than PV, it is immediately bounded to the PV.

- Create a Pod with PVC

`kubectl create -f pod-with-pvc.yaml --kubeconfig=$HOME/.kube/config-gce`

#### Auto-provisioning

- Delete all previous PV/PVC, pod

```
kubectl delete pvc myclaim --kubeconfig=$HOME/.kube/config-gce
kubectl delete pv pv0003 --kubeconfig=$HOME/.kube/config-gce
kubectl delete pod mypod --kubeconfig=$HOME/.kube/config-gce
```

- Create a PVC with special label

`kubectl create -f pod-with-pvc.yaml --kubeconfig=$HOME/.kube/config-gce`

kubernetes will create a PV for you (and the actual underline disk), and bind your PVC
with the new PV.

- Delete the PVC will also delete PV and the disk

`kubectl delete pod mypod --kubeconfig=$HOME/.kube/config-gce`
`kubectl delete pvc myclaim --kubeconfig=$HOME/.kube/config-gce`
