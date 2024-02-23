#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

	pid_t parent_pid, child_pid, grandchild_pid;
	int child_count = 0, grandchild_count = 0;

	child_pid = fork();

	if (child_pid < 0)
	{
		perror("Error creating a child process");
		exit(1);
	}
	else if (child_pid == 0)
	{
		child_count++;
		child_pid = getpid();
		parent_pid = getppid();
		printf("Child Process: PID = %d, PPID = %d\n", child_pid, parent_pid);
		printf("Total no of child process = %d\n", child_count);

		grandchild_pid = fork();

		if (grandchild_pid < 0)
		{
			perror("Error creating grandchild process");
			exit(1);
		}
		else if (grandchild_pid == 0)
		{
			grandchild_count++;
			grandchild_pid = getpid();
			child_pid = getppid();
			printf("Grandchild Process : PID = %d, PPID = %d \n", grandchild_pid, child_pid);
			printf("My roll no is CSM23005\n");
			printf("Total no of grand child process = %d\n", grandchild_count);
			exit(0);
		}
		else
		{
			wait(NULL);
			exit(0);
		}
	}
	else
	{
		wait(NULL);
		// printf("Process & their ID : Parent PID = %d, Child PID = %d, Grandchild PID = %d \n", parent_pid, child_pid, grandchild_pid);
		// printf("Total no of child process = %d\n", child_count);
		// printf("Total no of grandchild process = %d\n", grandchild_count);
		exit(0);
	}

	return 0;
}
