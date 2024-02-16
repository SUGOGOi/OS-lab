#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int cnt_child_p = 0;
    int cnt_grandchild_p = 0;
    pid_t child_p, grandchild_p;
    child_p = fork();
    if (child_p < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (child_p == 0)
    {
        cnt_child_p++;
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());
        printf("Total number of child processes: %d\n", cnt_child_p);
        char *args[] = {"./child.out", NULL};
        printf("overlay userdefine program:\n");
        execv(args[0], args);
        perror("execv");
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        wait(&status);

        printf("\nParent Process: PID = %d, PPID = %d\n", getpid(), getppid());

        if (WIFEXITED(status))
        {
            printf("Child process terminated normally with exit status: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Child process terminated abnormally\n");
        }
    }
    return 0;
}