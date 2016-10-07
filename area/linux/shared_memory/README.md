### Shared memory IPC example

#### System V

http://stackoverflow.com/questions/4582968/system-v-ipc-vs-posix-ipc
http://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html

#### Posix

http://stackoverflow.com/questions/21311080/linux-shared-memory-shmget-vs-mmap
http://www.cse.psu.edu/~deh25/cmpsc473/notes/OSC/Processes/shm.html
https://www.ibm.com/developerworks/aix/library/au-spunix_sharedmemory/

compile with `gcc shm_posix.c -lrt`, rt stands for 'real time extension library'

### Notes

Posix style uses mmap, which stands for 'memory mapped file', see mmapdemo.c for
an example. It maps a file region into process's address space. If your OS has
/dev/shm/ (/run/shm), then shm_open is equivalent to opening a file in /dev/shm/,
and mmap is mapping that file into address space. Everything happens in memory.
