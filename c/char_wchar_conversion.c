/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-05-20 13:52:29
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-05-20 15:04:41
 */
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

int main(int argc, char *argv)
{
    //wchar_t to char
    //加个L表示是wchar_t类型的字符串，否则转换时会出错
    wchar_t *wstr = L"hello world";
    size_t len = wcslen(wstr) + 1;
    printf("%d\n", len);
    size_t converted = 0;
    char *str = (char *)malloc(len * sizeof(char));
    // wcstombs_s(&converted, str, len, wstr, _TRUNCATE);
    converted = wcstombs(str, wstr, len);
    printf("result:%s,converted length:%d\n", str, converted);

    return 0;
}