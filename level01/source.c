#include <stdio.h>
#include <string.h>
#include <unistd.h>

char a_user_name[100];

int verify_user_name() {
  puts("verifying username....\n");
  return (memcmp(a_user_name, "dat_wil", 7) != 0);
}

int verify_user_pass(char *buffer) {
  return (memcmp(buffer, "admin", 5) != 0);
}

int main(void) {
  char buffer[64];
  int bool;

  memset(buffer, 0, sizeof(buffer));
  bool = 0;
  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(a_user_name, 256, stdin);
  bool = verify_user_name();
  if (bool) {
    puts("nope, incorrect username...\n");
  } else {
    puts("Enter Password: ");
    fgets(buffer, 100, stdin);
    bool = verify_user_pass(buffer);
    puts("nope, incorrect password...\n");
  }
  return 1;
}
