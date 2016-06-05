#### cgroup example

ubuntu:
```
sudo apt-get install cgroup-bin
```

centos7:
```
sudo yum install libcgroup-tools
```

create cgroups: parent is limited to 12MB, and two children without setting limits:
```
sudo mkdir /sys/fs/cgroup/memory/test_parent
sudo mkdir /sys/fs/cgroup/memory/test_parent/child1
sudo mkdir /sys/fs/cgroup/memory/test_parent/child2

sudo bash -c "echo 12582912 > /sys/fs/cgroup/memory/test_parent/memory.limit_in_bytes"
sudo bash -c "echo 12582912 > /sys/fs/cgroup/memory/test_parent/memory.memsw.limit_in_bytes"
```

build and run `mem_limit.c` in two terminals:
```
gcc mem_limit.c
sudo cgexec -g memory:/test_parent/child1 ./a.out
sudo cgexec -g memory:/test_parent/child2 ./a.out
```

child1 (or child2) will be killed when their **total** allocated memory is 12MB;
then other one will proceed since memory is freed. This demonstrated the hierarchy
tree property of cgroup.