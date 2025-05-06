#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char buffer[100];
  unsigned int i;

  fgets(buffer, 100, stdin);
  for (i = 0; i < strlen(buffer); ++i) {
    if (buffer[i] > 64 && buffer[i] <= 90)
      buffer[i] ^= 32;
  }
  printf(buffer);
  exit(0);
}
