#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int pid = fork();
    if (pid) {                //parent
        printf("%i\n", pid);
        return 0;
    } else {
        chdir("/");           // Child
        
        setsid(); //int child_pid = setsid();
        //printf("daemon: %i\n", child_pid);
        while (1) {
            // Do nothing 
        }
    }
}
