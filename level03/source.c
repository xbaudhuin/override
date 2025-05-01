#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int decrypt(char c) {
  unsigned int i;
  unsigned int j;
  int tab[7];

  tab[1] =
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
