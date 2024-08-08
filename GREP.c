#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    char fname[10], pattern[10], temp[200];
    FILE *fp;
    printf("\nEnter the filename: ");
    scanf("%s", fname);
    printf("\nEnter the pattern to be searched: ");
    scanf("%s", pattern);
    fp = fopen(fname, "r");
    while (!feof(fp))
    {
        fgets(temp, 100, fp);
        if (strstr(temp, pattern))
            printf("%s", temp);
    }
    fclose(fp);
}
