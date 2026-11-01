#include <stdio.h>
#include <stdint.h>

/* 打印 uint32 的二进制，32 位全打，每 4 位一个空格 */
void print_bin(uint32_t v)
{
  for (int i = 31; i >= 0; i--)
  {
    putchar((v >> i) & 1u ? '1' : '0');
    if (i % 4 == 0 && i != 0)
      putchar(' ');
  }
  putchar('\n');
}

/* 打印 uint16 的二进制，16 位全打，每 4 位一个空格 */
void print_bin16(uint32_t v)
{
  for (int i = 15; i >= 0; i--)
  {
    putchar((v >> i) & 1u ? '1' : '0');
    if (i % 4 == 0 && i != 0)
      putchar(' ');
  }
  putchar('\n');
}

uint32_t odr = 0x00000000;
void gpio_write_bsrr(uint32_t bsrr) {
  odr &= ~(bsrr >> 16);         /* 高 16 位：清 0 —— 先清 */
  odr |= (bsrr & 0x0000FFFF);   /* 低 16 位：置 1 —— 后置，置位赢 */
  print_bin16((bsrr & 0x0000FFFF));
  // return bsrr;
}
void make_t8_1(uint32_t x){
  uint8_t *p = (uint8_t*) &x;
  for(int i = 0 ; i< 4; i++) {
    printf(" 0x%02x\t",  p[i]);
  }
}
void make_t8_2(uint32_t x){
  uint32_t mask = 0xff;
  for(int i = 0 ; i< 4; i++) {
    printf(" 0x%02x\t", ((x >> (8 * i)) & mask));
  }
}

int gpio_set_mode(uint32_t *crl, int pin, uint32_t mode){
  if(pin < 0 || pin > 7) return -1;
  if(mode > 0xf) return -1;

  // pin 指开始修改的位置
  // mode 指修改进去的值（变量名好奇怪
  uint32_t mask = ((1u << 4) -1) << (pin * 4);
  // 修改寄存器
  *crl &= ~(mask); // 取反
  *crl |= (mode << (pin * 4)) & mask;
  return 0;

}
int main(){
  printf("第7题: \n");
  gpio_write_bsrr(0x00003456);
  print_bin(odr);
  gpio_write_bsrr(0x00020000);
  print_bin(odr);
  gpio_write_bsrr(0x00010001);
  print_bin(odr);
  printf("\n===============================\n");

  printf("第8题: 0xDE AD BE EF \n");
  make_t8_1(0xDEADBEEF);
  printf("\n-------------------------------\n");
  make_t8_2(0xDEADBEEF);
  printf("\n===============================\n");

  printf("第9题: \n");
  uint8_t c = 0xf0;
  printf("1.0xf0 + 0x20 = 0x%02X\t", c += 0x20);
  uint16_t b = 0xFFF0;
  printf("2.0xFFF0 + 0x20 = 0x%02X", b += 0x20);
  printf("\n===============================\n");

  printf("第10题: \n");
  uint32_t x = 0x12345678;
  gpio_set_mode(&x, 3, 0x1);
  print_bin(x);
  gpio_set_mode(&x, 9, 0x1);
  print_bin(x);
  gpio_set_mode(&x, 3, 0x18);
  print_bin(x);
  printf("\n===============================\n");


  return 0;
}