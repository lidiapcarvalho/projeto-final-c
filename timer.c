#include "timer.h"
#include <time.h>

double get_time_ms(void)
{
    struct timespec tempo;
    // cria uma variável que consegue guardar o tempo em duas partes

    clock_gettime(CLOCK_MONOTONIC, &tempo);
    // obtém o tempo atual usando o relógio monotónico

    return (double)tempo.tv_sec * 1000.0 +
            (double)tempo.tv_nsec / 1000000.0;
    // tv_sec -> segundos
    // tv_nsec -> nanosegundos
}
