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
    printf("=== 危险演示 1：置位用「加 8」 ===\n");
    uint32_t a = 0x00000008;          /* bit3 已经是 1 */
    printf("原值      : "); print_bin(a);
    printf("+8 之后   : "); print_bin(a + 8);
    printf("|= (1<<3) : "); print_bin(a | (1u << 3));
    printf("  -> 加法把 bit3 的进位推到了 bit4，置位变成了改两位\n\n");

    printf("=== 危险演示 2：清位用「减 128」 ===\n");
    uint32_t b = 0x00000000;          /* bit7 已经是 0 */
    printf("原值          : "); print_bin(b);
    printf("-128 之后     : "); print_bin(b - 128);
    printf("&= ~(1<<7)    : "); print_bin(b & ~(1u << 7));
    printf("  -> 减法借位，把高位全变成 1 了\n\n");

    printf("=== 第 3 题：正确掩码是 0xFF00 ===\n");
    uint32_t x = 0x0000FF00;
    printf("原值          : "); print_bin(x);
    printf("^ 0x0000FF00  : "); print_bin(x ^ 0x0000FF00);
    printf("^ 0x00008100  : "); print_bin(x ^ 0x00008100);
    printf("  -> 你写的 0x8100 只翻转了 bit8 和 bit15，中间 6 位没动\n\n");

    printf("=== 第 5 题：bit8-11 是 >>8，不是 >>12 ===\n");
    uint32_t R = 0x12345678;
    printf("R               : "); print_bin(R);
    printf("(R >> 8)  & 0xF : 0x%X   <- bit 8..11\n", (R >> 8) & 0xF);
    printf("(R >> 12) & 0xF : 0x%X   <- bit 12..15\n", (R >> 12) & 0xF);
    return 0;
}
