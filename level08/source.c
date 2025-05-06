#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

uint64_t log_wrapper(FILE *stream, const char *message, const char *filename) {
  char dest[264];
  uint64_t stack_canary;

  stack_canary = read_gs_dword(40);
  strcpy(dest, filename);
  snprintf(&dest[strlen(dest)], 254 - strlen(dest), filename);
  dest[strcspn(dest, "\n")] = '\0';
  fprintf(stream, "LOG: %s\n", dest);
  return read_gs_dword(40) ^ stack_canary;
}

int main(int ac, char **av) {
  FILE *stream_log;
  FILE *stream;
  int fd;
  char buf;
  char dest[104];
  long stack_canary;

  stack_canary = read_gs_dword(40);
  if (ac != 2) {
    printf("Usage: %s filename\n", *av);
  }
  stream_log = fopen("./backups/.log", "w");
  if (stream_log == NULL) {
    printf("ERROR: Failed to open %s\n", "./backups/.log");
    exit(1);
  }
  log_wrapper(stream_log, "Starting back up: ", av[1]);
  stream = fopen(av[1], "r");
  if (stream == 0) {
    printf("ERROR: Failed to open %s\n", av[1]);
    exit(1);
  }
  strcpy(dest, "./backups/");
  strncat(dest, av[1], 99 - strlen(dest));
  fd = open(dest, O_RDWR | O_CREAT | O_TRUNC | O_EXCL, 0660);
  if (fd < 0) {
    printf("ERROR: Failed to open %s%s\n", "./backups/", av[1]);
    exit(1);
  }
  while (1) {
    buf = fgetc(stream);
    if (buf == -1)
      break;
    write(fd, &buf, stdout);
  }
  log_wrapper(stream_log, "Finished back up ", av[1]);
  fclose(stream);
  close(fd);
  return 0;
}
