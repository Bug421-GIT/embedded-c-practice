#include <stdio.h>
#include <stdint.h>
int main(void){
    uint32_t x = 0x12345678u;
    x |= (1u << 8);
    printf("after set bit8 : 0x%08X\n", x);
    x &= ~0xFu;
    printf("after clear low4: 0x%08X\n", x);
    printf("bit20 is %u\n", (x >> 20) & 1u);
    return 0;
}
