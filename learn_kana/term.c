#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void to_stdout(const char *str) {
  while (*str) {
    fputc(*str, stdout);
    str++;
  }
}

struct termios setup() {
  struct termios saved, cbreaky;
  tcgetattr(STDIN_FILENO, &saved);
  cbreaky = saved;
  cbreaky.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &cbreaky);
  return saved;
}

void clean(struct termios *saved) { tcsetattr(STDIN_FILENO, TCSAFLUSH, saved); }
