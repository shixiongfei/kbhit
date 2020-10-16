/*
 *  kbhit.c
 *
 *  copyright (c) 2020 Xiongfei Shi
 *
 *  author: Xiongfei Shi <jenson.shixf(a)gmail.com>
 *  license: Apache-2.0
 *
 *  https://github.com/shixiongfei/kbhit
 */

#include "kbhit.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static struct termios orig_termios;

static void reset_terminal_mode(void) {
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void setup_terminal_mode(void) {
  struct termios new_termios;

  tcgetattr(STDIN_FILENO, &orig_termios);
  new_termios = orig_termios;
  new_termios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

  atexit(reset_terminal_mode);
}

int kbhit(void) {
  int oldf, ch;

  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int getch(void) { return getchar(); }
