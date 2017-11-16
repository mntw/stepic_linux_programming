#include <stdio.h>
#include <string.h>
#include <dirent.h>

int count_all_children(int parent_pid)
{
    struct dirent *dirent;
    DIR *dir;
    dir = opendir("/proc");
    int count = 0;    
    while ((dirent = readdir(dir)) != NULL)
    {
        if (dirent->d_type == DT_DIR)
        {
            int pid = -1;
            sscanf(dirent->d_name, "%i", &pid);
            if (pid > 0)
            {
                char fname[255];
                sprintf(fname, "/proc/%i/status", pid);
                FILE *f = fopen(fname, "r");
                char buf[255];
                while (fgets(buf, sizeof(buf), f))
                {
                    char tag[255];
                    int ppid = -1;
                    sscanf(buf, "%s\t%i", tag, &ppid);
                    if (strcmp(tag, "PPid:") == 0 && ppid == parent_pid)
                    {
                        count = count + 1 + count_all_children(pid);
                    }
                }
                fclose(f);
            }                
        }            
    }
    closedir(dir);
    return count;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;
    
    int target_pid = -1;
    sscanf(argv[1], "%i", &target_pid);
    
    int count = count_all_children(target_pid);
    
    count++;
    printf("%i\n", count);
    return 0;
    
    
    return 0;
}
