/*
 * @Author: Bug421-GIT 576896275@qq.com
 * @Date: 2026-10-31 12:07:20
 * @LastEditors: Bug421-GIT 576896275@qq.com
 * @LastEditTime: 2026-10-31 13:54:45
 * @FilePath: \07-code\c-basics\bit-op-01-05.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdint.h>

/* 打印 uint32 的二进制，32 位全打，每 4 位一个空格 */
void print_bin(uint32_t v) {
    for (int i = 31; i >= 0; i--) {
        putchar((v >> i) & 1u ? '1' : '0');
        if (i % 4 == 0 && i != 0) putchar(' ');
    }
    putchar('\n');
}

int make_opt1() {
  int x = 0x00000000;
  return x | (1u << 3);
}
int make_opt2() {
  int x = 0xFFFFFFFF;
  return x & ~(1u << 7);
}
int make_opt3(){
  int x = 0x0000FF00;
  uint32_t mask = ((1u << 8) - 1) << 8;
  return x ^ mask;
}
// 4. `R = 0x12345678`，读出 bit 20 的值，打印 `0` 或 `1`。
int make_opt4() {
  int x= 0x12345678;
  return (x >> 20) & 1u;
}
// 5. `R = 0x12345678`，读出 bit 8 到 bit 11（4 位），打印成一个十六进制数
int make_opt5() {
  int x= 0x12345678;
  return (x >> 8) & 0xf;
}
int main(void) {
  printf(" 第 1 题 从 `0x00000000` 开始，只把 bit 3 置 1，打印结果: \n");
  int opt1 = make_opt1();
  print_bin(opt1);
  printf(" 值位，将目标位数值置1 \n");

  printf(" 第 2 题 从 `0xFFFFFFFF` 开始，只把 bit 7 清 0，打印结果: \n");
  int opt2 = make_opt2();
  print_bin(opt2);
  printf(" 清位，将目标位数值置0 \n");

  printf(" 第 3 题 从 `0x0000FF00` 开始，把 bit 8 到 bit 15 全部翻转，打印结果: \n");
  int opt3 = make_opt3();
  print_bin(opt3);
  printf(" 翻转，将对于位数的电路开的关，关的开 \n");

  printf(" 第 4 题 R = 0x12345678`，读出 bit 20 的值，打印结果: \n");
  int opt4 = make_opt4();
  printf("%X \n",opt4);
  printf(" 对于对应位数的电路状态查询 \n");

  printf(" 第 5 题`R = 0x12345678`，读出 bit 8 到 bit 11（4 位），打印成一个十六进制数: \n");
  int opt5 = make_opt5();
  printf("%X \n",opt5);

  return 0;
}





//

// 5. `R = 0x12345678`，读出 bit 8 到 bit 11（4 位），打印成一个十六进制数字。
// 和上一题的写法有什么区别？