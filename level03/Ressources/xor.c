#include <stdio.h>
#include <string.h>

int main(void) {
  char str[] = "Q}|u`sfg~sf{}|a3";
  const char *to_match = "Congratulations!";
  size_t len = strlen(str);

  for (char i = 1; i < 22; i++) {
    for (int j = 0; j < len; j++) {
      str[j] ^= i;
    }
    if (strcmp(str, to_match) == 0) {
      printf("Value = %d\n", (int)i);
      return 0;
    } else {
      strcpy(str, "Q}|u`sfg~sf{}|a3");
    }
  }
}
