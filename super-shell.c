#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

int main (void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	FILE *stream = fopen("/dev/stdin", "r");

	if (!stream)
	{
		perror("fopen failed");
		exit(1);
	}

	while (1)
	{
		/*prompt*/
		write(1, "$ ", 2);

		nread = getline(&line, &len, stream);
		if (nread == -1)
			break;

		/*ligne vide*/
		if (nread == 1)
			continue;

		 /* supprimer le '\n' final */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* fork */
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(1);
		}

		/* fils */
		else if (pid == 0)
		{
			char *argv[2];
    		argv[0] = line;
    		argv[1] = NULL;

			/* exécuter la commande */
			execve(argv[0], argv, NULL);
			/* i échec exit(1) */
			perror("execve failed");
			exit(1);
		}
		/* père */
		else
		{
			/* attendre que le fils finisse */
			wait(&status);
		}
	}
	/* libérer mémoire */
	free(line);
	fclose(stream);
	return (0);
}
