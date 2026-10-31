#include <stdio.h>

/* 情况 A：全局变量，不加 volatile */
int g_flag = 0;
/* 情况 B：全局变量，加 volatile */
volatile int gv_flag = 0;

/* 情况 C：局部变量，不加 volatile */
void local_test(void) {
    int l_flag = 0;
    while (l_flag == 0) { }
}

/* 情况 D：局部变量，加 volatile */
void local_volatile_test(void) {
    volatile int lv_flag = 0;
    while (lv_flag == 0) { }
}

/* 情况 A 的实现 */
void global_test(void) {
    while (g_flag == 0) { }
}

/* 情况 B 的实现 */
void global_volatile_test(void) {
    while (gv_flag == 0) { }
}

int main(void) {
    global_test();
    return 0;
}
