#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *layout;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    if (argc != 2)
    {
        printf("please specify the layout file\n");
        exit(1);
    }

    layout = fopen(argv[1], "r");
    if (layout == NULL)
    {
        printf("open layout file failed\n");
        exit(2);
    }
    while ((nread = getline(&line, &len, layout)) != EOF)
    {
        printf("line length:%zu, line content:%s\n", nread, line);
    }
    printf("file read completely\n");

    free(line);
    fclose(layout);
    exit(0);
}