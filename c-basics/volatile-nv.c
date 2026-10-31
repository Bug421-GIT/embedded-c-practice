/*
 * @Author: Bug421-GIT 576896275@qq.com
 * @Date: 2026-10-31 17:56:47
 * @LastEditors: Bug421-GIT 576896275@qq.com
 * @LastEditTime: 2026-10-31 17:57:55
 * @FilePath: \07-code\c-basics\volatile-nv.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <stdint.h>

int flag = 0;

void wait_flag(void)
{
  while (flag == 0)
  {
  }
}

int main(void)
{
  wait_flag();
  return 0;
}