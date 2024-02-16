#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
    pid_t pid;
    int signal_number;

    printf("Enter Process ID: ");
    scanf("%d", &pid);

    printf("Enter Signal number: ");
    scanf("%d", &signal_number);

    if (kill(pid, signal_number) == -1)
    {
        perror("kill");
        exit(EXIT_FAILURE);
    }

    return 0;
}