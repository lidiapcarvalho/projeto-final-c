#include "timer.h"
#include <time.h>

double get_time_ms(void)
{
    struct timespec tempo;
    // cria uma variável que consegue guardar o tempo em duas partes

    clock_gettime(CLOCK_MONOTONIC, &tempo);
    // obtém o tempo através de um relógio monotónico, adequado para medir intervalos de tempo, pois não depende da hora do sitema e não deve andar para trás.

    return (double)tempo.tv_sec * 1000.0 +
            (double)tempo.tv_nsec / 1000000.0;
    // tv_sec -> segundos, por isso é multiplicado por 1 000 para converter para milissegundos
    // tv_nsec -> nanosegundos, por isso é dividido por 1 000 000 para converter para milissegundos
    // estes dois valores são depois somados para obter uma única medida de tempo em milissegundos
    // double permite guardar também a parte decimal dos milissegundos, permitindo obter valores como 24510.5 ms, que depois podem ser apresentados como 24.51 s.
}
