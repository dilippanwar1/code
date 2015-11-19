### Run this to generate rootfs
```
docker export $(docker create busybox) > busybox.tar && rm -rf rootfs && mkdir rootfs && tar -C rootfs -xf busybox.tar && rm -rf busybox.tar
```

### Then start
```
sudo runc start
```
