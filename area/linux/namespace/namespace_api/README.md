#### Notes from https://lwn.net/Articles/531381

- The namespace API consists of three system calls—clone(), unshare(), and setns() — and a number of /proc files.
- As with most other namespaces (user namespaces are the exception), creating a UTS namespace requires privilege
  (specifically, CAP_SYS_ADMIN).
- API: Creating a child in a new namespace: clone()
- API: Joining an existing namespace: setns()
  - More precisely, setns() disassociates the calling process from one instance of a particular namespace type and
    reassociates the process with another instance of the same namespace type.
- API: The unshare() system call provides functionality similar to clone(), but operates on the calling process:
  it creates the new namespaces specified by the CLONE_NEW* bits in its flags argument and makes the caller a member
  of the namespaces.
- Leaving aside the other effects of the clone() system call, a call of the form:
  ```c
  clone(..., CLONE_NEWXXX, ....);
  ```
  is roughly equivalent, in namespace terms, to the sequence:
  ```
  if (fork() == 0)
    unshare(CLONE_NEWXXX);      /* Executed in the child process */
  ```
