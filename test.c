/*
 *  test.c
 *
 *  copyright (c) 2020 Xiongfei Shi
 *
 *  author: Xiongfei Shi <jenson.shixf(a)gmail.com>
 *  license: Apache-2.0
 *
 *  https://github.com/shixiongfei/kbhit
 */

#include "kbhit.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  setup_terminal_mode();

  while (!kbhit())
    printf("Hit me!\n");

  printf("Key is '%c'\n", getch());
  return 0;
}
