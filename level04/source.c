#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {

  char str[128];
  pid_t pid;

  pid = fork();
  memset(str, 0, 128);
}
