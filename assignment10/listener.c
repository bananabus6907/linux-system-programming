#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    key_t key = 987654;
    int shmid;
    char *shared_mem;

    // 공유 메모리 생성 또는 접근
    if ((shmid = shmget(key, 100, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    // 공유 메모리 attach
    if ((shared_mem = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Listener 시작 - 수신 대기 중...\n");

    while (1) {
        if (strlen(shared_mem) > 0) {
            printf("Listener 수신: %s\n", shared_mem);
            if (strncmp(shared_mem, "exit", 4) == 0)
                break;
            shared_mem[0] = '\0'; // 읽었으니 초기화
        }
        sleep(1); // 주기적으로 확인
    }

    shmdt(shared_mem); // detach
    shmctl(shmid, IPC_RMID, NULL); // 공유 메모리 제거
    return 0;
}
