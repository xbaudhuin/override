#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int nb;

  puts("***********************************");
  puts("* \t     -Level00 -\t\t  *");
  puts("***********************************");
  printf("Password:");
  scanf("%d", &nb);
  if (nb == 5276) {
    puts("\nAuthenticated!");
    system("/bin/sh");
    return 0;
  } else {
    puts("\nInvalid Password!");
    return 1;
  }
}
