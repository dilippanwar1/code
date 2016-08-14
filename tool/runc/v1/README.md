## runc example

### Create rootfs
```
mkdir rootfs
docker export $(docker create busybox) | tar -C rootfs -xvf -
```

### To start a container using runc:
```sh
cd busybox
sudo runc start
```

Same for ubuntu
