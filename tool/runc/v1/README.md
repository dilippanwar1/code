## runc example

### Create rootfs

```sh
mkdir busybox
cd busybox
mkdir rootfs
docker export $(docker create busybox) | tar -C rootfs -xvf -
```

The above commands create rootfs for container, we'll also need config.json.
Following command generates a default config.json.

```sh
runc spec
```

### To start a container using runc:

```sh
cd busybox
sudo runc run mycontainerid
```
