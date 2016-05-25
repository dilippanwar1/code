// A simple syslog example, see http://linux.die.net/man/3/syslog
//
// syslog is a standard for message logging. It permits separation of the
// software that generates messages, the system that stores them, and the
// software that reports and analyzes them.  Note most operating system
// supports syslog, including Mac and linux.
//
// $ ps aux | grep syslog
//  This will show that syslogd deamon is running.
#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
  openlog("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
  syslog(LOG_NOTICE, "Program started by User %d", getuid ());
  syslog(LOG_INFO, "A tree falls in a forest");
  closelog ();
}
