#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
        argc = 0, argv = NULL;
        int pid = fork();
        if (pid == 0) {
                printf("Child\n");
                sleep(100);
                exit(0);
        } else if (pid > 0) {
                int status;
                //int new_pid;
                pid_t pid_child;
                printf("Pai\n");
                //new_pid = fork();
                //if (new_pid == 0) exit(0);
                pid_child = waitpid(pid, &status, WIFEXITED(status));
                printf("%d\n", status);
        }
        return 0;
}
