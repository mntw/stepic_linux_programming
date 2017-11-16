#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, int ** argv) {
    struct dirent *dirent;
    DIR *dir;
    dir = opendir("/proc");
    int count = 0;
    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_type == DT_DIR) {
            int pid = -1;
            sscanf(dirent->d_name, "%i", &pid);
            if (pid > 0) {
                char fname[255];
                sprintf(fname, "/proc/%i/status", pid);
                FILE *f = fopen(fname, "r");
                char buf[255];
                while (fgets(buf, sizeof(buf), f)) {
                    char tag[255];
                    char data[255];
                    sscanf(buf, "%s\t%s", tag, data);
                    if (strcmp(tag, "Name:") == 0 && strcmp(data, "genenv") == 0)
                        count++;
                }
                fclose(f);
            }                
        }            
    }
    closedir(dir);
    printf("%i\n", count);
    return 0;
}
