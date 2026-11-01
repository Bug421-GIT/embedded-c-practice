/*
 * @Author: Bug421-GIT 576896275@qq.com
 * @Date: 2026-11-01 11:30:05
 * @LastEditors: Bug421-GIT 576896275@qq.com
 * @LastEditTime: 2026-11-01 11:30:20
 * @FilePath: \07-code\c-basics\volatile-ptr.c
 * @Description: */
#include <stdio.h>
#include <stdint.h>

/* 模拟一个硬件寄存器 */
uint32_t fake_register = 0x12345678;

/* 情况 A：普通指针 */
void read_normal(void) {
    uint32_t *p = &fake_register;
    uint32_t a = *p;
    uint32_t b = *p;
    uint32_t c = *p;
    printf("%u %u %u\n", a, b, c);
}

/* 情况 B：指向 volatile 的指针 */
void read_volatile(void) {
    volatile uint32_t *p = &fake_register;
    uint32_t a = *p;
    uint32_t b = *p;
    uint32_t c = *p;
    printf("%u %u %u\n", a, b, c);
}

int main(void) {
    read_normal();
    read_volatile();
    return 0;
}