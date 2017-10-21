#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>

int (*ldFunction)(int);

bool init_lib(char * libname, char * f_name){
    void *hdl = dlopen(libname, RTLD_LAZY);
    if (NULL == hdl) {
        printf("Can't open %s library\n", libname);
        return false;
    }
    ldFunction = (int (*) (int)) dlsym (hdl, f_name);
    if (NULL == ldFunction) {
        printf("Can't find  %s function\n", f_name);
        return false;
    }
    return true;
}


int main (int argc, char * argv[]) {
    if (argc != 4) {
        printf("Wrong parameters.\n");
        exit(0);
    }
    char * libname = argv[1];
    char * f_name = argv[2];
    int value = atoi(argv[3]);
    //printf("libname: %s\nfunction name: %s\nvalue: %d\n", libname, f_name, value);
    if (init_lib(libname, f_name)) {
        printf("%d\n", ldFunction(value)); 
    } else {
        printf("Library was not loaded\n");
    }

    return 0;
}
