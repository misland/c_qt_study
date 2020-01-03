#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main()
{
    FILE *fp;
    int errnum;
    fp=fopen("unexists.txt","rb");
    if(fp==NULL)
    {
        errnum=errno;
        fprintf(stderr,"Error Number:%d\n",errno);
        perror("Output error message by perror");
        //strerror就是根据错误值返回错误描述
        fprintf(stderr,"Open file error:%s\n",strerror(errnum));
    }
    else
    {
        fclose(fp);
    }

    return 0;
    
}