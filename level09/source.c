#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_msg {
  char message[140];
  int64_t username[5]; // char username[40]
  int len;
} t_msg;

int secret_backdoor(void) {
  char buffer[128];

  fgets(buffer, 128, stdin);
  return system(buffer);
}

char *set_msg(t_msg *message) {
  char str[1024];
  memset(str, 0, sizeof(str));
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets(str, 1024, stdin);
  return strncpy(message->message, str, message->len);
}

int set_username(t_msg *message) {
  char str[140];
  int i;

  memset(str, 0, 128);
  puts(">: Enter your username");
  printf(">>: ");
  fgets(str, 128, stdin);
  for (i = 0; i <= 40 && str[i]; ++i) {
    *(char *)(message + i + 140) = str[i];
    // *(char *)message->username[i] = str[i]
  }
  return printf(">: Welcome, %s", (const char *)(message->username));
}

int handle_msg(void) {
  t_msg message;
  set_username(&message);
  set_msg(&message);
  return puts(">: Msg sent!");
}

int main(void) {
  puts("--------------------------------------------\n"
       "|   ~Welcome to l33t-m$n ~    v1337        |\n"
       "--------------------------------------------");
  handle_msg();
  return 0;
}
