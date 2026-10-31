#include <stdio.h>
#include <stdint.h>
#include <limits.h>

void print_bin(uint32_t v) {
    for (int i = 31; i >= 0; i--) {
        putchar((v >> i) & 1u ? '1' : '0');
        if (i % 4 == 0 && i != 0) putchar(' ');
    }
    putchar('\n');
}

/* 早期写法：返回 int。n=31 时 (1u<<31)-1 = 0x7FFFFFFF 恰好放得下，
 * 但调用方若期望"32 位掩码"就会误判；真正的坑见演示 1/2。 */
int mask_int(int n) { return (1u << n) - 1; }
/* 更稳的写法：uint32_t */
uint32_t mask_u32(int n) { return (1u << n) - 1; }

int main(void) {
    printf("=== 演示 1：想要 32 位全 1，写成 (1u<<32)-1 会得到 0 ===\n");
    printf("(1u<<31)-1 = 0x%08X  <- 31 位全 1，正确\n", (uint32_t)((1u << 31) - 1));
    printf("x86 上移位量按 32 取模，所以 1u<<32 等价于 1u<<0\n");
    printf("(1u<<32)-1 = 0x%08X  <- 全 0，不是 0xFFFFFFFF\n", (uint32_t)((1u << 0) - 1));
    printf("  -> 要 32 位全 1，直接写 0xFFFFFFFFu 或 ~0u\n\n");

    printf("=== 演示 2：有符号左移溢出是未定义行为 ===\n");
    printf("INT_MAX = %d (0x7FFFFFFF)\n", INT_MAX);
    printf("mask_u32(31) 走无符号 = %u\n", mask_u32(31));
    printf("若写成 (1 << 31)（有符号），结果依赖编译器，不可移植\n\n");

    printf("=== 演示 3：XOR 造掩码 vs &~ 造掩码 ===\n");
    /* 你的写法：a ^ b */
    uint32_t a1 = mask_u32(12), b1 = mask_u32(4);
    printf("a=0xFFF, b=0xF\n");
    printf("  a ^ b    = 0x%03X  <- 你的写法\n", a1 ^ b1);
    printf("  a & ~b   = 0x%03X  <- 更直白的写法\n", a1 & ~b1);
    printf("  (a-b)    = 0x%03X  <- 题目的提示\n", a1 - b1);
    printf("  三者相同，因为 b 的位全在 a 里面，没有借位/进位\n\n");

    printf("=== 演示 4：XOR 什么时候会错 ===\n");
    uint32_t a2 = mask_u32(4), b2 = mask_u32(12);   /* 参数反了 */
    printf("a=0xF, b=0xFFF（参数写反）\n");
    printf("  a ^ b    = 0x%03X  <- XOR 对称，还是 0xFF0\n", a2 ^ b2);
    printf("  a & ~b   = 0x%03X  <- 变成 0，语义就暴露了\n", a2 & ~b2);
    printf("  -> XOR 会把参数写反藏起来，&~ 不会\n");
    return 0;
}
