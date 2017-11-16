#include <stdio.h>
#include <string.h>

int getppid(int pid)
{
    char fname[255];
    sprintf(fname, "/proc/%i/status", pid);
    char buf[255];
    FILE *f = fopen(fname, "r");    
    int ppid;
    while (fgets(buf, sizeof(buf), f))
    {
        char tag[255];
        ppid = -1;
        sscanf(buf, "%s\t%i", tag, &ppid);
        if (strcmp(tag, "PPid:") == 0)        
            break;
    }
    fclose(f);
    return ppid; 
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;    
    int pid, ppid;
    sscanf(argv[1], "%i", &pid);
    printf("%i\n", pid);
    ppid = getppid(pid);
    while (ppid != 1)
    {
        printf("%i\n", ppid);
        ppid = getppid(ppid);
    }
    printf("1\n");
    return 0;
}
