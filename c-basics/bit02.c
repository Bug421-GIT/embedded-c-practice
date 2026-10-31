#include <stdio.h>
#include <stdint.h>

int main(void) {
    /* 1. 位编号：最低位是 bit 0 */
    uint16_t R = 0x0F0F;
    printf("R        = 0x%04X\n", R);
    for (int b = 0; b <= 15; b++) {
        if (b == 4 || b == 11) printf("  bit %2d = %u  <- 本题用的位\n", b, (R >> b) & 1u);
    }
    printf("1 << 0  = 0x%04X   (最低位，最右边)\n", 1u << 0);
    printf("1 << 4  = 0x%04X\n", 1u << 4);
    printf("1 << 11 = 0x%04X\n", 1u << 11);
    printf("1 << 15 = 0x%04X   (最高位，最左边)\n\n", 1u << 15);

    /* 2. 第7题验算 */
    uint16_t a = R | (1u << 4);
    uint16_t b = a & ~(1u << 11);
    printf("0x0F0F | (1<<4)  = 0x%04X\n", a);
    printf("0x0F1F & ~(1<<11) = 0x%04X\n\n", b);

    /* 3. BCD：每位十进制单独存 4 位 */
    uint8_t dec = 59;
    uint8_t bcd = (uint8_t)(((dec / 10) << 4) | (dec % 10));
    printf("十进制 59 的普通二进制 = 0x%02X\n", dec);
    printf("十进制 59 的 BCD       = 0x%02X  (十位%d=0101, 个位%d=1001)\n", bcd, dec/10, dec%10);
    printf("把 BCD 读回十进制      = %u\n", (bcd >> 4) * 10 + (bcd & 0x0F));
    printf("0xC3 高半字节 = %u，超过 9，不是合法 BCD 位\n", 0xC3 >> 4);
    return 0;
}
