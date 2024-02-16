#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc >= 1)
    {
        printf("Child process called: %s", argv[0]);
    }
    else
    {
        printf("No program found");
    }
    return 0;
}