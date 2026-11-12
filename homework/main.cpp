#include <stdlib.h>
#include <stdio.h>

int main() {
    char *val;
    val = getenv("LANG");
    if (val == NULL)
        printf("LANG not defined\n");
    else
        printf("현재 LANG = %s\n", val);
    setenv("LANG", "ko_KR.UTF-8", 1);
    val = getenv("LANG");
    printf("변경된 LANG = %s\n", val);
    return 0;
}
