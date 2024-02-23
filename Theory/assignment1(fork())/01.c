#include <stdio.h>
#include <unistd.h>

int main()
{
    if (fork() || fork())
    {
        fork();
    }
    printf("1");
    printf("\n");
}