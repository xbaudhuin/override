#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// function added by the canary protection
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

int decrypt(char c) {
  unsigned int i;
  unsigned int len;
  uint32_t tab[7];

  *((char *)&tab[4] + 1) = read_gs_dword(20);
  strcpy((char *)tab, "Q}|u`sfg~sf{}|a3");
  len = strlen((const char *)tab);
  for (i = 0; i < len; ++i) {
    *((char *)tab + i) ^= c;
  }
  if (!strcmp((const char *)tab, "Congratulations!"))
    return system("/bin/sh");
  else
    return puts("\nInvalid Password");
}

int test(int save, int b) {
  int result;
  char c;

  if (b - save <= 21 && b - save > 0) {
    result = decrypt(b - save);
  } else {
    c = rand();
    result = decrypt(c);
  }
  return result;
}

int main(void) {
  time_t current_time;
  int save;

  current_time = time(0);
  srand(current_time);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  scanf("%d", &save);
  test(save, 322424845);
  return 0;
}
