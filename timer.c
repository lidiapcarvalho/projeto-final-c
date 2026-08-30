#include "timer.h"
#include <time.h>

double get_time_ms(void)
{
    struct timespec tempo;

    clock_gettime(CLOCK_MONOTONIC, &tempo);

    return (double)tempo.tv_sec * 1000.0 +
            (double)tempo.tv_nsec / 1000000.0;
}
