#include <stdio.h>
#include <time.h>

int main(void)
{
    struct timespec tempo;

    clock_gettime(CLOCK_MONOTONIC, &tempo);

    printf("Tempo: %ld segundos\n", tempo.tv_sec);

    return 0;
}
