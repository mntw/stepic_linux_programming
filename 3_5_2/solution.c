#include <stdio.h>

int main () {
    FILE * ptrFile = fopen("/proc/self/stat", "r");
    char string [10];
    fscanf(ptrFile, "%*s %*s %*s %s", string);
    printf("%s\n", string);
    return 0;
}
