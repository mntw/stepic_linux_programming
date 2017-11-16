#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv)
{
    int fd1 = open("in1", O_NONBLOCK | O_RDONLY);
    int fd2 = open("in2", O_NONBLOCK | O_RDONLY);
    int maxfd = (fd1 > fd2) ? fd1 : fd2; 
    int sum = 0;
    int not_closed1 = 1, not_closed2 = 1; 
    while (not_closed1 || not_closed2)
    {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(fd1, &readset);
        FD_SET(fd2, &readset);
        select(maxfd + 1, &readset, NULL, NULL, NULL);
        ssize_t count1, count2;
        char buf[4096];
        if (FD_ISSET(fd1, &readset))
        {
            count1 = read(fd1, buf, 4096);
            if (count1 == 0) not_closed1 = 0;
            for (int i = 0; i < count1; i++)
                if (buf[i] >= '0' && buf[0] <= '9')
                    sum += (int) buf[i] - (int) '0';
        }
        if (FD_ISSET(fd2, &readset))
        {
            count2 = read(fd2, buf, 4096);
            if (count2 == 0) not_closed2 = 0;
            for (int i = 0; i < count1; i++)
                if (buf[i] >= '0' && buf[0] <= '9')
                    sum += (int) buf[i] - (int) '0';
        }
    }
    printf("%i\n", sum);
    return 0;
}
