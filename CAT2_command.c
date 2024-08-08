#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;
    char ch;
    if (argc < 3)
    {
        printf("Insufficient number of arguments!\n");
        exit(1);
    }
    fp1 = fopen(argv[1], "a");
    fp2 = fopen(argv[2], "r");
    if (fp2 == NULL)
    {
        printf("The file to be appended does not exist");
        exit(1);
    }
    while ((ch = fgetc(fp2)) != EOF)
        fprintf(fp1, "%c", ch);
    fclose(fp1);
    fclose(fp2);
}