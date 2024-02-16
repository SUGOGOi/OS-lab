#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <utmp.h>

void print_logged_in_users()
{
    struct utmp *utmp_entry;
    setutent();

    while ((utmp_entry = getutent()) != NULL)
    {
        if (utmp_entry->ut_type == USER_PROCESS)
        {
            printf("Logged in user: %s\n", utmp_entry->ut_user);
        }
    }

    endutent(); // Close utmp file
}

int main()
{
    pid_t pid, grandpid;

    // Create first child process
    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed!\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());

        // Create grandchild process
        grandpid = fork();

        if (grandpid < 0)
        {
            fprintf(stderr, "Grandchild process creation failed!\n");
            exit(1);
        }
        else if (grandpid == 0)
        {
            // Grandchild process
            print_logged_in_users(); // Print logged in users
            exit(0);
        }
        else
        {
            // Child process (after creating grandchild)
            printf("Child process: Grandchild PID = %d\n", grandpid);
            exit(0);
        }
    }
    else
    {
        // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        printf("Parent process exiting normally.\n");
        exit(0);
    }

    return 0; // Unreachable code
}