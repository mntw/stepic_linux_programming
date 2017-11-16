#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE_SM 1000 /* make it a 1K shared memory segment */
#define COUNT 100

int main(int argc, char *argv[]) {
    key_t key_1 = atoi(argv[1]);
    key_t key_2 = atoi(argv[2]);
    key_t key = ftok("solution.c", 'a'); /*Here the file must exist */

    if (key == -1) {
        printf("ftok error\n");
    }

    // fprintf(stderr, "%d\n", key);
    // fprintf(stderr, "%d\n", key_1);
    // fprintf(stderr, "%d\n", key_2);

    /*  create the segment: */
    int shmid = shmget(key, SIZE_SM, IPC_CREAT | 0666);
    int *arr = (int*)shmat(shmid, 0, 0);

    /* attach to the segment to get a pointer to it: */
    int shmid_1 = shmget(key_1, SIZE_SM, 0666);
    int *arr_shmaddr_1 = (int*)shmat(shmid_1, 0, 0);
    int shmid_2 = shmget(key_2, SIZE_SM, 0666);
    int *arr_shmaddr_2 = (int*)shmat(shmid_2, 0, 0);

    // fprintf(stderr, "%d\n", shmid);
    // fprintf(stderr, "%d\n", shmid_1);
    // fprintf(stderr, "%d\n", shmid_2);

    memset(arr, 0, SIZE_SM);

    if (arr == (int*)(-1)) {
        fprintf(stderr, "err0\n");
    }
    if (arr_shmaddr_1 == (int*)(-1)) {
        fprintf(stderr, "err1\n");
    }
    if (arr_shmaddr_2 == (int*)(-1)) {
        fprintf(stderr, "err2\n");
    }

    int i;
    for (i = 0; i < COUNT; i++) {
        arr[i] = arr_shmaddr_1[i] + arr_shmaddr_2[i];
        // fprintf(stderr, "%d=%d+%d:\n", arr[i], arr_shmaddr_1[i], arr_shmaddr_2[i]);
    }

    /* detach from the segment: */
    if (shmdt(arr) == -1) {
        fprintf(stderr, "err5\n");
    }
    if (shmdt(arr_shmaddr_1) == -1) {
        fprintf(stderr, "err6\n");
    }
    if (shmdt(arr_shmaddr_2) == -1) {
        fprintf(stderr, "err7\n");
    }
    printf("%d\n", key);
    return 0;
}
