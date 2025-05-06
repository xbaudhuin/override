#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

  int stat_loc;
  char str[128];
  int var;
  int var2;
  pid_t pid;
  int trace;

  pid = fork();
  memset(str, 0, 128);
  trace = 0;
  stat_loc = 0;
  if (pid) {
    do {
      wait(&stat_loc);
      var = stat_loc;
      if ((stat_loc & 0x7f) == 0 || (var2 = stat_loc),
          (char)((stat_loc & 0x7f) + 1) >> 1 > 0) {
        puts("child is exiting...");
        return (0);
      }
      trace = ptrace(PTRACE_PEEKUSER, pid, 44, 0);
    } while (trace != 11);
    puts("no exec() for you");
    kill(pid, 8);
  } else {
    prctl(1, 1);
    ptrace(PTRACE_TRACEME, 0, 0, 0);
    puts("Give me some shellcode, k");
    gets(str);
  }
  return (0);
}
