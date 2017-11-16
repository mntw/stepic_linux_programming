#include <stdio.h>
#include <signal.h>

int sum1 = 0, sum2 = 0, finished = 0;

void signal_handler(int sig_num)
{
    if (sig_num == SIGUSR1) sum1++;
    else if (sig_num == SIGUSR2) sum2++;
    else if (sig_num == SIGTERM) finished = -1;
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGTERM, signal_handler);
}

int main(int argc, char** argv)
{
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGTERM, signal_handler);
    while (!finished) {};
    printf("%i %i\n", sum1, sum2);
    return 0;
}
