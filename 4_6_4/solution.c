#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sighandler(int sigid)
{
    exit(0);
}

int main()
{
    int pid = fork();
    if (pid)
    {
        // Parent
        printf("%i\n", pid);
        return 0;
    } else
    {
        // Child
        chdir("/");
        //int child_pid = 
        setsid();
        //printf("daemon: %i\n", child_pid);
        signal(SIGURG, sighandler);
        while (1)
        {
            // Do nothing 'till the end of time
        }
    }
}
