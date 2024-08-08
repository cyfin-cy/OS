#include <stdio.h>
void main()
{
    char fn[10];
    printf("Enter source filename\n");
    scanf("%s", fn);
    if ((remove(fn)) == 0)
        printf("File is removed!");
    else
        printf("File is not removed!");
}
