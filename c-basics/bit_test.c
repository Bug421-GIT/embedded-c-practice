#include <stdio.h>
int main(void) {
    unsigned int x = 0x12345678;
    printf("原值      = 0x%08X\n", x);
    printf("置第8位   = 0x%08X\n", x | (1u << 8));
    printf("清最低4位 = 0x%08X\n", x & ~0xFu);
    printf("第20位    = %u\n", (x >> 20) & 1u);
    return 0;
}