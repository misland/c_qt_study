/*
 * @Description: demo for endian
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-03-31 15:14:24
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-07-14 15:20:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv)
{
  int num = 0x12345678; // 十进制是305419896
  printf("length of num:%d\n", sizeof(num));
  for (int i = 0; i < sizeof(num); i++)
  {
    // 将其转为char*，是为了强制程序只取一位，以观察每一位的具体数值
    char tem = *((char *)(&num + i));
    // 依次打印78 56 34 12
    // 小端存储是内存低位存放的是数字的低位
    // windows目前绑定x86，而x86是小端
    // int占了4个字节，打印结果第一二三四个字节存放的是78、56、34、12
    printf("num[%d]:%x\n", i, tem);
  }

  return 0;
}