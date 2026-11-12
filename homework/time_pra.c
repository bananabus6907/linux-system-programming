#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <time.h>

int main() {
    int i;
    time_t t;
    struct tms start_buf, end_buf;
    clock_t t1, t2;
    long ticks;

    ticks = sysconf(_SC_CLK_TCK);
    printf("Clock tick per second: %ld\n", ticks);

    if ((t1 = times(&start_buf)) == -1) {
        perror("times (start)");
        exit(1);
    }

    int fd = open("temp_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char msg[] = "Hello, system call!\n";
    size_t msg_len = strlen(msg);
    for (i = 0; i < 1000000; i++) {
        if (write(fd, msg, msg_len) < 0) {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    close(fd);

    sleep(1);

    if ((t2 = times(&end_buf)) == -1) {
        perror("times (end)");
        exit(1);
    }

    printf("Start clock ticks (t1): %ld\n", t1);
    printf("End clock ticks (t2): %ld\n", t2);
    printf("Real Time       : %.2f sec\n", (double)(t2 - t1) / ticks);
    printf("User Time       : %.2f sec\n", (double)(end_buf.tms_utime - start_buf.tms_utime) / ticks);
    printf("System Time     : %.2f sec\n", (double)(end_buf.tms_stime - start_buf.tms_stime) / ticks);
    printf("User + System   : %.2f sec\n",
           ((double)(end_buf.tms_utime - start_buf.tms_utime) +
            (double)(end_buf.tms_stime - start_buf.tms_stime)) / ticks);

    double real_time = (double)(t2 - t1) / ticks;
    double user_time = (double)(end_buf.tms_utime - start_buf.tms_utime) / ticks;
    double system_time = (double)(end_buf.tms_stime - start_buf.tms_stime) / ticks;

    return 0;
}
