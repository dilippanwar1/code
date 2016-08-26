### Minimal kernel module example

- Run `make` to compile
- Run `sudo insmod hello.ko` to load kernel module
- Run `dmesg` to see module init message
- Run `sudo rmmod hello` to remove kernel module
- Run `dmesg` to see module exit message
- Run `make clean` to clean up
