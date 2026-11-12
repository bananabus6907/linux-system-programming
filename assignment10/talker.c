#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = 987654;
    int shmid;
    char *shared_mem;
    char input[100];

    // 공유 메모리 접근
    if ((shmid = shmget(key, 100, 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((shared_mem = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        printf("Talker 입력: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // 줄바꿈 제거

        strcpy(shared_mem, input);

        if (strcmp(input, "exit") == 0)
            break;
    }

    shmdt(shared_mem);
    return 0;
}
