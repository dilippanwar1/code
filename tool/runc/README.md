## runC example

### Create rootfs
```
docker export $(docker create busybox) > busybox.tar
```

### To start a container using runC:
```sh
cd busybox
sudo runc start
```

Same for ubuntu
