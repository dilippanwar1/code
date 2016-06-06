// The user namespace allows a process to have root privileges within the
// namespace, without giving it that access to processes outside of the
// namespace.
//  $ gcc userns.c -lcap
// Required libcap-dev.
//
// From https://lwn.net/Articles/532593/, https://lwn.net/Articles/540087/
// - When a user namespace is created, the first process in the namespace is
//   granted a full set of capabilities in the namespace.
// - If a user ID has no mapping inside the namespace, then system calls that
//   return user IDs return the value defined in the file /proc/sys/kernel/overflowuid,
//   which on a standard system defaults to the value 65534. Initially, a user
//   namespace has no user ID mapping, so all user IDs inside the namespace map
//   to this value.
// - Although the new process has a full set of capabilities in the new user
//   namespace, it has no capabilities in the parent namespace. This is true
//   regardless of the credentials and capabilities of the process that calls
//   clone(). In particular, even if root employs clone(CLONE_NEWUSER), the
//   resulting child process will have no capabilities in the parent namespace.
// - If the process opening the file is in the same user namespace as the process
//   PID, then ID-outside-ns is defined with respect to the parent user namespace.
//   If the process opening the file is in a different user namespace, then
//   ID-outside-ns is defined with respect to the user namespace of the process
//   opening the file.
// - It is also possible to include additional CLONE_NEW* flags in the same
//   clone() (or unshare()) call that employs CLONE_NEWUSER to create the new
//   user namespace. In this case, the kernel guarantees that the CLONE_NEWUSER
//   flag is acted upon first, creating a new user namespace in which the
//   to-be-created child has all capabilities. The kernel then acts on all of the
//   remaining CLONE_NEW* flags, creating corresponding new namespaces and making
//   the child a member of all of those namespaces.

#define _GNU_SOURCE
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <sys/capability.h>

#define STACK_SIZE (1024*1024)

static char child_stack[STACK_SIZE];
char * const child_args[]={
  "/bin/bash",
  NULL
};

void set_uid_map(int inside_id,int outside_id,int length) {
  char path[256];
  sprintf(path,"/proc/%d/uid_map", getpid());
  printf("%s\n", path);
  FILE* uid_map = fopen(path, "w");    // open file '/proc/[pid]/uid_map'
  fprintf(uid_map,"%d %d %d\n", inside_id, outside_id, length);
  fclose(uid_map);
}

void set_gid_map(int inside_id, int outside_id, int length) {
  char path[256];
  sprintf(path,"/proc/%d/gid_map", getpid());
  printf("%s\n", path);
  FILE* gid_map = fopen(path,"w");
  fprintf(gid_map, "%d %d %d\n", inside_id, outside_id, length);
  fclose(gid_map);
}

int child_main(void * args) {
  printf("In child_main, pid:%d, uid:%d, gid:%d\n", getpid(), getuid(), getgid());
  printf("eUID = %ld; eGID = %ld\n", (long)geteuid(), (long)getegid());
  set_uid_map(0, 1000, 1);
  set_gid_map(0, 1000, 1);
  printf("eUID = %ld; eGID = %ld\n", (long)geteuid(), (long)getegid());
  cap_t caps;
  caps = cap_get_proc();
  printf("capabilities:%s\n", cap_to_text(caps, NULL));
  execv(child_args[0], child_args);
  return 1;
}

int main() {
  int child_pid = clone(
    child_main, child_stack + STACK_SIZE, SIGCHLD|CLONE_NEWUSER, NULL);
  printf("Child PID: %d\n", child_pid);
  waitpid(child_pid, NULL, 0);
  return 0;
}
