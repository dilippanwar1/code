// Linux also maintains a data structure for all the mountpoints of the system.
// It includes information like what disk partitions are mounted, where they
// are mounted, whether they are readonly, et cetera. With Linux namespaces,
// one can have this data structure cloned, so that processes under different
// namespaces can change the mountpoints without affecting each other.
