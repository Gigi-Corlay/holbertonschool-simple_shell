#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t pid = getpid();
    printf("PID du processus courant : %d\n", pid);
    return 0;
}