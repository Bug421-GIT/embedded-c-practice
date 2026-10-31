/*
 * @Author: Bug421-GIT 576896275@qq.com
 * @Date: 2026-10-31 13:58:38
 * @LastEditors: Bug421-GIT 576896275@qq.com
 * @LastEditTime: 2026-10-31 17:29:51
 * @FilePath: \07-code\c-basics\bit-op-10-15.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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
// `uint32_t x = 0xDEADBEEF`，打印它的**四个字节**（从低地址到高地址），用 `uint8_t*` 强转
void make_opt10(uint32_t x)
{
  uint8_t *p = (uint8_t*) & x;
  for (int i = 0; i < 4; i++){
    printf("p[%d] = 0x%02X\n", i, p[i]);
  }

}
// uint8_t a = 0x5A`，把它的**高 4 位和低 4 位互换
uint8_t make_opt12()
{
  uint8_t a = 0x5A;
  uint8_t mask = 0x0f;
  uint8_t low = (a & mask) << 4;
  uint8_t hight = (a >> 4) & mask;
  return low | hight;
}

uint32_t make_opt13()
{
  uint32_t x = 0x44444444;
  uint32_t mask = ((1u << 8) - 1) ^ ((1u << 4) - 1);
  uint32_t init = x & ~mask;
  uint32_t result = init | (0x8 << 4);
  return result;
}

uint32_t gpio_write_bsrr(uint32_t odr, uint32_t bsrr) {
  odr &= ~(bsrr >> 16);       /* 高 16 位：写 1 复位 */
  odr |= (bsrr & 0x0000FFFF); /* 低 16 位：写 1 置位，后执行所以置位优先 */
  return odr;
}

int make_opt15(uint32_t num) {
  int count = 0;
  while (num)
  {
    if(num & 1) count ++;
    num >>= 1;
  }
  return count;
};

int main(void)
{
  // `uint32_t x = 0xDEADBEEF`，打印它的**四个字节**（从低地址到高地址），用 `uint8_t*` 强转。
  printf(" 第 10 题 `uint32_t x = 0xDEADBEEF`四个字节（从低地址到高地址）： \n");
  uint32_t x10 = 0xDEADBEEF;
  make_opt10(x10);
  printf("  \n");

  printf(" 第 11 题 用位操作（不用指针）从 `0xDEADBEEF` 里**单独取出*）： \n");
  uint32_t x11 = 0xDEADBEEF;
  printf(" 最低字节： 0x%02X \n", x11 & 0xff);
  printf(" 第二个字节： 0x%02X \n", (x11 >> 8) & 0xff);
  printf(" 最高字节： 0x%02X \n", (x11 >> 24) & 0xff);
  printf("  \n");

  printf(" 第 12 题 `uint8_t a = 0x5A`，把它的**高 4 位和低 4 位互换**，打印结果: \n");
  int opt12 = make_opt12();
  print_bin(opt12);
  printf("  \n");

  printf(" 第 13 题 初始CRL = 0x44444444只改 bit 4-7，其他位一个都不能动，打印结果: \n");
  int opt13 = make_opt13();
  print_bin(opt13);
  printf("  \n");

  printf(" 第 14 题 \n");
  uint32_t odr = 0;
  odr = gpio_write_bsrr(odr, 0x00000005);   print_bin(odr);
  odr = gpio_write_bsrr(odr, 0x00000002);   print_bin(odr);
  odr = gpio_write_bsrr(odr, 0x00020000);   print_bin(odr);
  odr = gpio_write_bsrr(odr, 0x00010001);   print_bin(odr);
  printf("  \n");

  printf(" 第 15 题 \n");
  // int opt15 = make_opt15();
  printf("%d, ",make_opt15(0x00000000));
  printf("%d, ",make_opt15(0xFFFFFFFF));
  printf("%d, ",make_opt15(0x12345678));
  printf("%d  ",make_opt15(0x80000000));
  // print_bin(opt15);
  printf("  \n");
  return 0;
}