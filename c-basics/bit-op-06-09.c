/*
 * @Author: Bug421-GIT 576896275@qq.com
 * @Date: 2026-10-31 12:45:34
 * @LastEditors: Bug421-GIT 576896275@qq.com
 * @LastEditTime: 2026-10-31 13:57:02
 * @FilePath: \07-code\c-basics\bit-op-06-09.c
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

// 6. 构造一个"低 8 位全 1、其余全 0"的掩码，打印。
// 要求用 `(1u << n) - 1` 的形式，不要直接写 `0xFF`。
uint32_t make_opt6(int n){
  return (1u << n) - 1;
}

// 7. 构造一个"bit 4 到 bit 11 全 1、其余全 0"的掩码，打印。
// 提示：先想"低 12 位全 1"减去"低 4 位全 1"。
uint32_t make_opt7(int n, int m){
  uint32_t a = make_opt6(n);
  uint32_t b = make_opt6(m);
  return a ^ b;

}

// 8. `R = 0x12345678`，把 bit 4 到 bit 11 这 8 位整体清零，其余不动，打印结果。
// （这是寄存器配置里最常见的操作：先清掉一段，再写新值）
int make_opt8(){
  int x = 0x12345678;
  uint32_t z = make_opt7(12, 4);
  return x & ~z;
}

// 9. 接着第 8 题的结果，把这 8 位写入 `0xAB`，打印结果。
// （先清后写，两步。想想为什么不能直接 `|=`）
int make_opt9(){
  int x = make_opt8();
  return x | (0xAB << 4);
}

int main(void) {
  printf(" 第 6 题 构造一个'低 8 位全 1、其余全 0'的掩码，打印结果: \n");
  int opt6 = make_opt6(8);
  print_bin(opt6);
  printf("  \n");

  printf(" 第 7 题 构造一个'bit 4 到 bit 11 全 1、其余全 0'的掩码，打印结果: \n");
  int opt7 = make_opt7(12,4);
  print_bin(opt7);
  printf("  \n");


  printf(" 第 8 题 `R = 0x12345678`，把 bit 4 到 bit 11 这 8 位整体清零，其余不动，打印结果: \n");
  int opt8 = make_opt8();
  print_bin(opt8);
  printf("  \n");

  printf(" 第 9 题 接着第 8 题的结果，把这 8 位写入 `0xAB`，打印结果: \n");
  int opt9 = make_opt9();
  print_bin(opt9);
  printf("  \n");
}