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
#ifdef _WIN32
#include <conio.h>
#else /* _WIN32 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#endif /* _WIN32 */

#ifndef _WIN32
static struct termios orig_termios;

static void reset_terminal_mode(void) {
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
#endif /* _WIN32 */

void setup_terminal_mode(void) {
#ifndef _WIN32
  struct termios new_termios;

  tcgetattr(STDIN_FILENO, &orig_termios);
  new_termios = orig_termios;
  new_termios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

  atexit(reset_terminal_mode);
#endif /* _WIN32 */
}

int kbhit(void) {
#ifdef _WIN32
  return _kbhit();
#else /* _WIN32 */
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
#endif /* _WIN32 */
}

int getch(void) {
#ifdef _WIN32
  return _getch();
#else /* _WIN32 */
  return getchar();
#endif /* _WIN32 */
}
