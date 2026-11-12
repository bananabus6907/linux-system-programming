#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


int main() {
    int pipe1[2]; // 부모 → 자식
    int pipe2[2]; // 자식 → 부모
    pid_t pid;
    char buffer[128];

    // 파이프 생성
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        // 부모 프로세스
        close(pipe1[0]); // 자식에게 보내는 파이프의 읽기 닫음
        close(pipe2[1]); // 자식으로부터 받는 파이프의 쓰기 닫음

        // 자식에게 메시지 전송
        char *msg = "Hello Child";
        write(pipe1[1], msg, strlen(msg) + 1);
        close(pipe1[1]);

        // 자식으로부터 메시지 수신
        read(pipe2[0], buffer, sizeof(buffer));
        printf("부모 프로세스에서 받은 메시지: %s\n", buffer);
        close(pipe2[0]);

    } else {
        // 자식 프로세스
        close(pipe1[1]); // 부모에게서 받는 파이프의 쓰기 닫음
        close(pipe2[0]); // 부모에게 보내는 파이프의 읽기 닫음

        // 부모로부터 메시지 수신
        read(pipe1[0], buffer, sizeof(buffer));
        printf("자식 프로세스에서 받은 메시지: %s\n", buffer);
        close(pipe1[0]);

        // 부모에게 메시지 전송
        char *msg = "Hello Parent";
        write(pipe2[1], msg, strlen(msg) + 1);
        close(pipe2[1]);
    }

    return 0;
}
