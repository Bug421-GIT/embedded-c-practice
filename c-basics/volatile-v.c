/*
 * @Author: Bug421-GIT 576896275@qq.com
 * @Date: 2026-10-31 18:00:14
 * @LastEditors: Bug421-GIT 576896275@qq.com
 * @LastEditTime: 2026-10-31 18:00:27
 * @FilePath: \07-code\c-basics\volatile-v.c
 * @Description:
 */
#include <stdio.h>
#include <stdint.h>

volatile int flag = 0;

void wait_flag(void) {
    while (flag == 0) { }
}

int main(void) {
    wait_flag();
    return 0;
}