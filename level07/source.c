#include <stdint.h>
#include <stdio.h>
#include <string.h>

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

void clear_stdin() {
  int result;

  do {
    result = getchar();
    if ((char)result == '\n')
      return;
  } while ((char)result != -1);
  return;
}

int get_unum() {
  int index[3];
  index[0] = 0;
  fflush(stdout);
  scanf("%u", index);
  clear_stdin();
  return index[0];
}

int store_number(int *index) {
  unsigned int unum;
  unsigned int v3;

  printf(" Number: ");
  unum = get_unum();
  printf(" Index: ");
  v3 = get_unum();
  if ((v3 % 3) == 0 || (unum >= 3070230528 && unum <= 3087007743)) {
    /* if ((v3 % 3) == 0 || (unum >> 0x18 == 0xb7)) { */
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
  } else {
    *(int *)(index + 4 * v3) = unum;
    /* index[v3] = unum; */
    return 0;
  }
}

int read_number(int *index) {
  int unum;

  printf(" Index: ");
  unum = get_unum();
  printf("  Number at data[%u] is %u\n", unum, *(int *)(index + 4 * unum));
  return 0;
}

int main(int ac, char **av, char **env) {
  char buffer[400];
  int number;
  char str[20] = {0};
  unsigned int stack_canary;

  stack_canary = read_gs_dword(20);
  number = 0;
  memset(buffer, 0, sizeof(buffer));
  // zero'ed all av and env
  while (*av) {
    memset((void *)*av, 0, strlen(*av));
    ++av;
  }
  while (*env) {
    memset((void *)*env, 0, strlen(*env));
    ++env;
  }
  puts("----------------------------------------------------\n"
       "  Welcome to wil's crappy number storage service!   \n"
       "----------------------------------------------------\n"
       " Commands:                                          \n"
       "    store - store a number into the data storage    \n"
       "    read  - read a number from the data storage     \n"
       "    quit  - exit the program                        \n"
       "----------------------------------------------------\n"
       "   wil has reserved some storage :>                 \n"
       "----------------------------------------------------\n");

  while (1) {
    printf("Input command: ");
    number = 1;
    fgets(str, 20, stdin);
    str[strlen(str) - 1] = 0;
    if (memcmp(str, "store", 5) == 0) {
      number = store_number((int *)buffer);
    } else if (memcmp(str, "read", 4) == 0) {
      number = read_number((int *)buffer);
    } else if (memcmp(str, "quit", 4) == 0) {
      return 0;
    }
    if (number != 0) {
      printf(" Failed to do %s command\n", str);
    } else {
      printf(" Completed %s command successfully\n", str);
    }
    memset(str, 0, sizeof(str));
  }
  return 0;
}
