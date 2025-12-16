#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
	pid_t pid;
	int i, status;

	char *argv[] = {"ls", "-l", "/tmp", NULL};

	for (i = 0; i < 5; i++)
	{
		pid = fork();

		if (pid == -1)  // Erreur
		{
			perror("fork failed");
			exit(1);
		}
		else if (pid == 0)
		{
			execve("/bin/ls", argv, environ);
			perror("execve failed");
			exit(1);
		}
		else
			wait(&status);
	}
	return (0);
}
