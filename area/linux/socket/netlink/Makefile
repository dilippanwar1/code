KDIR := /lib/modules/$(shell uname -r)/build

obj-m += netlink_kernel.o

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	gcc netlink_user.c -o netlink_user

clean:
	rm -rf *.o *.ko *.mod.* *.cmd .module* modules* Module* .*.cmd .tmp* netlink_user
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
