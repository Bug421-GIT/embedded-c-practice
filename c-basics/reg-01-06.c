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

void make_bit32(int tnum, uint32_t crl, int hi, int low, uint8_t new){
  printf("第%d题: \n",tnum);
  uint32_t mask = ((1u << 4) - 1) << low;
  uint32_t clearCrl = crl & ~mask;
  // 限定修改范围：与掩码求和
  uint32_t lawfulNew = (new << low) & mask;
  uint32_t inputCrl = clearCrl | lawfulNew;

  printf("inputCrl:");
  print_bin(inputCrl);
  uint8_t text1 = (inputCrl & mask ) >> low;
  printf("text1: 0x%02X\n",text1);
  uint8_t text2 = (inputCrl & (((1u << 4) - 1) << (hi + 1))) >> (hi + 1);
  printf("text2: 0x%02X\n",text2);
  printf("===============================\n");
}
void make_bit16(int tnum, uint16_t crl, int hi, int low, uint8_t new){
  printf("第%d题: \n",tnum);
  uint16_t mask = ((1u << 4) - 1) << low;
  printf("mask:0x%02X,",mask);
  print_bin16(mask);

  uint16_t clearCrl = crl & ~mask;
  // 限定修改范围：与掩码求和
  uint16_t lawfulNew = (new << low) & mask;
  uint16_t inputCrl = clearCrl | lawfulNew;
  printf("inputCrl:0x%02X,", inputCrl);
  print_bin16(inputCrl);
  uint8_t text1 = (inputCrl & mask ) >> low;
  printf("text1: 0x%02X\n",text1);
  uint8_t text2 = (inputCrl & (((1u << 4) - 1) << (hi + 1))) >> (hi + 1);
  printf("text2: 0x%02X\n",text2);
  printf("===============================\n");
}

uint32_t set_field(uint32_t reg, int n, int width, uint32_t val){
// 把 `reg` 的 bit n 到 bit n+width-1 改成 `val`，返回新的寄存器值
  uint32_t maks = ((1u << (width)) - 1) << n;
  reg &= ~maks;
  reg |= (val << n) & maks;
  print_bin(reg);
  return reg;
}

int main()
{
  make_bit32(1, 0x44444444, 7, 4, 0x08);
  make_bit32(2, 0x44444444, 15, 12, 0x3);
  // 第三题在上面打印里
  make_bit16(4, 0x0f0f, 12, 9, 0xa);
  make_bit32(5, 0x12345678, 23, 20, 0xb);

  printf("第6题: \n");
  uint32_t crl = 0x44444444;
  printf("第0次调用: ");
  print_bin(crl);
  printf("第1次调用: ");
  crl = set_field(crl, 4, 4, 0x8);
  printf("第2次调用: ");
  crl = set_field(crl, 12, 4, 0x3);   /* PA3 → 0x3 */
  printf("第3次调用: ");
  crl = set_field(crl, 0, 2, 0x3);    /* PA0 低 2 位 → 0b11 */
  printf("===============================\n");

  return 0;
}