#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Wrong argument count!\n");
        return 1;
    }
    char *cmd = malloc(strlen(argv[1]) + strlen(argv[2]) + 2);
    strcpy(cmd, argv[1]);
    strcat(cmd, " ");
    strcat(cmd, argv[2]);
    //printf("Command is: %s\n", cmd);
    
    FILE *fd = popen(cmd, "r");
    //printf("popen result is: %i\n", fd);
    int count = 0;
    char c;
    while ((c = fgetc(fd)) != EOF) {
        //printf("Read: %c (%i)\n", c, c);
        if (c == '0') count++;
    }
        
    
    pclose(fd);
    printf("%i\n", count);
    return 0;
}
