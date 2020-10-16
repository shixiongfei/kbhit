/*
 *  kbhit.h
 *
 *  copyright (c) 2020 Xiongfei Shi
 *
 *  author: Xiongfei Shi <jenson.shixf(a)gmail.com>
 *  license: Apache-2.0
 *
 *  https://github.com/shixiongfei/kbhit
 */

#ifndef __KBHIT_H__
#define __KBHIT_H__

#ifdef __cplusplus
extern "C" {
#endif

void setup_terminal_mode(void);
int kbhit(void);
int getch(void);

#ifdef __cplusplus
};
#endif

#endif /* __KBHIT_H__ */
