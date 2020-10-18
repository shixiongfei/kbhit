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
  tcsetattr(STDIN_FILENO, TCSADRAIN, &orig_termios);
}
#endif /* _WIN32 */

void setup_terminal_mode(void) {
#ifndef _WIN32
  struct termios new_termios;

  if (!isatty(STDIN_FILENO))
    return;

  tcgetattr(STDIN_FILENO, &orig_termios);
  new_termios = orig_termios;

  /* input modes: no break, no CR to NL, no parity check, no strip char,
   * no start/stop output control. */
  new_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  /* control modes - set 8 bit chars */
  new_termios.c_cflag |= (CS8);
  /* local modes - choing off, canonical off, no extended functions,
   * no signal chars (^Z,^C) */
  new_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  /* control chars - set return condition: min number of bytes and timer.
   * We want read to return every single byte, without timeout. */
  new_termios.c_cc[VMIN] = 1;  /* 1 byte  */
  new_termios.c_cc[VTIME] = 0; /* no timer */

  tcsetattr(STDIN_FILENO, TCSADRAIN, &new_termios);
  atexit(reset_terminal_mode);
#endif /* _WIN32 */
}

int kbhit(void) {
#ifdef _WIN32
  return _kbhit();
#else  /* _WIN32 */
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
#else  /* _WIN32 */
  return getchar();
#endif /* _WIN32 */
}
