#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <unistd.h>

// equivalent to the call of __readgsdword(0x14) since it doesnt directly exist
// in linux
// all for this line : mov    eax,gs:0x14
// read information on current thread
uint32_t read_gs_dword(uint32_t offset) {
  uint32_t value;
  __asm__ volatile("mov1 %%gs:(%1), %0"
                   : "=r"(value)
                   : "r"(offset)); // might be fs instead of gs
  return value;
}

int auth(char *buffer, int var) {
  int i;
  int v4;
  int len;

  buffer[strcspn(buffer, "\n")] = '\0';
  len = strnlen(buffer, 32);
  if (len <= 5)
    return 1;
  if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
    puts("\x1B[32m.---------------------------.");
    puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
    puts("\x1B[32m'---------------------------'");
    return 1;
  } else {
    v4 = (buffer[3] ^ 4919) + 6221293;
    for (i = 0; i < len; ++i) {
      if (buffer[i] <= 31)
        return 1;
      v4 += (v4 ^ (unsigned int)buffer[i]) % 1337;
    }
    return var != v4;
  }
}

__attribute__((noreturn)) void __stack_chk_fail(void);

int main(void) {
  int var;
  char buffer[32];
  unsigned int var2;

  var2 = read_gs_dword(20);
  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(buffer, 32, stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  scanf("%u", &var);

  if (auth(buffer, var) == 0) {
    puts("Authenticated!");
    system("/bin/sh");
  }
  if (var2 != read_gs_dword(20)) {
    // stack canary, detect if there was an overflow
    __stack_chk_fail();
  }
  return 0;
}
