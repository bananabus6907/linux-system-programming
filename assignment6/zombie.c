#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 > 0) {
        // 부모 프로세스
        printf("Parent (PID: %d) running.\n", getpid());
        pid2 = fork();
        if (pid2 == 0) {
            printf("Second child (PID: %d) exiting to become a zombie.\n", getpid());
            exit(0);
        }
        else {
        wait(NULL);
        }
        while(1) {
            sleep(1);
            printf("Parent still running (PID: %d).\n", getpid());
        }
    } else if (pid1 == 0) {
        printf("First child (PID: %d) running some long task.\n", getpid());
        sleep(10);
        exit(0);
    } else {
        perror("Failed to fork");
        return 1;
    }

    return 0;
}

