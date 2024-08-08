#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUF 30

int main()
{
    int fd = open("myfile.txt", O_RDWR), n;
    char buffer[BUF];
    printf("\nFile descriptor is %d\n", fd);
    if (fd == -1)
    {
        printf("File could not be opened");
        exit(0);
    }

    printf("\nReading the first 10 characters from file: \n");
    n = read(fd, buffer, 10);
    write(1, buffer, 10);
    printf("Skipping 5 chars from current position: \n");
    lseek(fd, 5, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(1, buffer, n);
    printf("Going to 5th last character: \n");
    lseek(fd, -5, SEEK_END);
    n = read(fd, buffer, 5);
    write(1, buffer, n);
    printf("Going to thrid character: \n");
    lseek(fd, 3, SEEK_SET);
    n = read(fd, buffer, 5);
    write(1, buffer, n);
    return 0;
}