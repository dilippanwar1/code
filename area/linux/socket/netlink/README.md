## Example netlink user-kernel communication

- Run `make` to build netlink_kernel.ko kernel module and others
- Run `sudo insmod netlink_kernel.ko` to load kernel module
- Run `./netlink_user.ko` to communicate to kernel
- Run `sudo rmmod netlink_kernel` to remove kernel module
- Run `dmesg` to see module exit message
- Run `make clean` to clean up
