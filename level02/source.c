#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char password[96];
  int var;
  char buffer[48];
  char username[96];
  int var2;
  int return_read;
  FILE *file;

  memset(password, 0, sizeof(password));
  var2 = 0;
  memset(buffer, 0, 41);
  memset(username, 0, sizeof(username));
  var = 0;
  file = NULL;
  return_read = 0;
  file = fopen("/home/users/level03/.pass", "r");
  if (file == 0) {
    fwrite("ERROR: failed to open username file\n", 1, 36, stderr);
    exit(1);
  }
  return_read = fread(buffer, 1, 41, file);
  buffer[strcspn(buffer, "\n")] = '\0';
  if (return_read != 41) {
    fwrite("ERROR: failed to read username file\n", 1, 36, stderr);
    fwrite("ERROR: failed to read username file\n", 1, 36, stderr);
    exit(1);
  }
  fclose(file);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ password: ");
  fgets(username, 100, stdin);
  username[strcspn(username, "\n")] = '\0';
  printf("--[ username: ");
  fgets(password, 100, stdin);
  password[strcspn(password, "\n")] = '\0';
  puts("*****************************************");
  if (strncmp(buffer, password, 41) != 0) {
    printf(username);
    puts(" does not have access");
    exit(1);
  }
  printf("Greetings, %s!\n", username);
  system("/bin/sh");
  return 0;
}
