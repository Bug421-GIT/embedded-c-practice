#include <stdio.h>
#include <windows.h>

int irq_flag = 0;                        /* 不加 volatile */
/* volatile int irq_flag = 0; */         /* 换成这行再跑 */

DWORD WINAPI irq_thread(LPVOID a) {
    (void)a;
    Sleep(1);                         /* 1 秒后，相当于"中断"来了 */
    irq_flag = 1;
    return 0;
}

int main(void) {
    CreateThread(NULL, 0, irq_thread, NULL, 0, NULL);
    printf("waiting...\n");
    while (irq_flag == 0) { }
    printf("got interrupt!\n");
    return 0;
}