#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid;
    pid = fork();
    if (pid > 0)
        printf("Pid %d\n", pid);
    else if (pid == 0) {
        char *options[] = {"-l"};
        execv("/bin/ls", options);
    }

    return 0;
}
