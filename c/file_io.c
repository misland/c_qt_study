/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2019-07-04 13:38:30
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2019-10-11 11:30:46
 */
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *test = NULL;
    test = fopen("C:\\a.txt", "w+");

    char *str = "hi there ,this is zgh\n";
    //fwrite方法中可以用\n换行
    fwrite(str, 1, strlen(str), test);
    //fputs方法中也可以用\n换行
    fputs("hello world\n hello too \n", test);

    //使用fprintf也可以将字符写入文件
    fprintf(test, "hi there \n");

    //fseek用于设置文件指针的位置，SEEK_SET表示文件头，1表示偏移量
    fseek(test, 1, SEEK_SET);
    //游标向前移了一位后，从游标中读一个字符，会读到i,读完游标会往前移一位
    printf("the second char is: %c \n", fgetc(test)); //the second char is: i
    //SEEK_CUR表示游标的当前位置，为负值时游标往后移
    fseek(test, -1, SEEK_CUR);
    //依然输出i，因为29行读取一个字符后游标前移一位，接着31行又把游标往后移了一位，又回到了原来的位置
    printf("current char is: %c \n", fgetc(test)); //current char is: i
    //SEEK_END表示游标的最后位置
    fseek(test, -5, SEEK_END);

    fseek(test, 0, SEEK_END);
    //把游标移到末尾，这时会进入if中
    if (fgetc(test) == EOF)
    {
        printf("move to the end of file \n");
    }
    else
    {
        printf("not the end of file \n");
    }

    //虽然可以插入字符，但是会把游标前面的内容一并插入，原因未知
    // fputc(65, test);
    char c;
    //getc执行后会自动将文件指针向后移动一个位置
    // while ((c = fgetc(test)) != EOF)
    // {
    //     printf("%c\n", c);
    // }

    fclose(test);
    return 0;
}