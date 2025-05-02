
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main(void) {
  char b[40];
  read(open(strdup("/home/users/level05/.pass"), O_RDONLY), b, 40);
  write(1, b, 40);
}
