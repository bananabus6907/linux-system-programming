#include <sys/sysinfo.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    struct sysinfo info;

    sysinfo(&info);

    printf("Total Ram: %ld\n", info.totalram);
    printf("Free Ram: %ld\n", info.freeram);
    printf("Num of Processes: %d\n", info.procs);
    pid_t getpid(void);
    pid_t getppid(void);


}