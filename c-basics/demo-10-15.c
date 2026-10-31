#include <stdio.h>
#include <stdint.h>

void print_bin(uint32_t v) {
    for (int i = 31; i >= 0; i--) {
        putchar((v >> i) & 1u ? '1' : '0');
        if (i % 4 == 0 && i != 0) putchar(' ');
    }
    putchar('\n');
}

int main(void) {
    printf("=== 第 10/11 题：移位取字节 ≠ 看内存 ===\n");
    uint32_t x = 0xDEADBEEF;
    printf("移位法（不管大小端都一样）:\n");
    for (int i = 0; i < 4; i++)
        printf("  (x>>%2d)&0xFF = 0x%02X\n", i*8, (x >> (8*i)) & 0xFF);

    printf("指针法（真正看内存布局）:\n");
    uint8_t *p = (uint8_t*)&x;
    for (int i = 0; i < 4; i++)
        printf("  p[%d] = 0x%02X\n", i, p[i]);

    printf("最高字节正确取法: (x >> 24) & 0xFF = 0x%02X\n", (x >> 24) & 0xFF);
    printf("你的 list10[4] 越界了，数组只有 4 个元素（下标 0-3）\n\n");

    printf("=== 第 14 题：函数返回了什么 ===\n");
    printf("你的 gpio_write_bsrr 返回的是 bsrr 本身，不是 odr\n");
    printf("所以打印出来就是输入原样回声\n\n");

    printf("=== 第 14 题：正确模拟（odr 必须是全局/静态）===\n");
    static uint32_t odr_spec = 0;
    static uint32_t odr_stu  = 0;
    uint32_t steps[3] = {0x00000005, 0x00020000, 0x00010001};
    for (int i = 0; i < 3; i++) {
        /* 题目给的顺序：先置后清 */
        odr_spec |= (steps[i] & 0x0000FFFF);
        odr_spec &= ~(steps[i] >> 16);
        /* 你的顺序：先清后置 */
        odr_stu &= ~(steps[i] >> 16);
        odr_stu |= (steps[i] & 0x0000FFFF);
        printf("第%d步 bsrr=0x%08X\n", i+1, steps[i]);
        printf("  题目顺序(先置后清) odr = "); print_bin(odr_spec);
        printf("  你的顺序(先清后置) odr = "); print_bin(odr_stu);
    }
    printf("\n第3步 0x00010001 = 同时置PA0和清PA0，顺序决定谁赢\n");
    printf("题目顺序 → bit0 = 0；你的顺序 → bit0 = 1\n\n");

    printf("=== 第 13 题验算 ===\n");
    uint32_t crl = 0x44444444;
    uint32_t mask = ((1u << 8) - 1) ^ ((1u << 4) - 1);
    uint32_t r = (crl & ~mask) | (0x8u << 4);
    printf("mask = 0x%08X\n", mask);
    printf("结果 = 0x%08X  = 0x44444484\n", r);
    return 0;
}
