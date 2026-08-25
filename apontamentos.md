## Caderno de Apontamentos

> Registo dos principais conceitos, funções e soluções explorados ao longo do desenvolvimento do projeto, com referências diretas ao código para facilitar a consulta.

### [`main.c`](main.c)

[`#include <locale.h>`](main.c#L5)
- localização/regionalização do programa (locale)

[`setlocale(LC_ALL, "");`](main.c#L12)
- Diz ao C, para usar as definições de idioma/codificação que o sistema operativo está a usar
- `setlocale()` -> configura o lacale do programa
- `LC_ALL` -> aplica a configuração a todas as categorias do locale
- `""` -> pede ao programa para usar o locale definido pelo ambiente/sistema operativo

[`initscr();`](main.c#L14)
- Inicializa o ncurses

[`keypad(stdscr, TRUE);`](main.c#L15)
- Permite ao ncurses reconhecer corretamente teclas especiais, como as setas

[`clock_t last_move = clock();`](main.c#L23) -> usada temporáriamente
- `clock_t` -> tipo de dado usado para guardar um valor produzido por clock()
- `clock()` -> devolve um valor que representa tempo de CPU utilizado pelo programa desde que começou

Diferenças comparativamente a double last_move = get_time_ms();
- clock() -> dependíamos do relógio do CPU
- get_time_ms() -> usamos o nosso temporizador baseado em tempo monotónico

[`clear();`](main.c#L30)
- Limpa o ecrã antes de desenharmos novamente

[`key = getch();`](main.c#L39)
- Faz o programa esperar por uma tecla
- Sem isto, o programa poderia desenhar a pista e terminar imediatamente

[`if (key != ERR)`](main.c#L64)
- ERR -> constante do ncurses que significa, neste contexto, "não foi recebida nenhuma tecla"

[`endwin()`](main.c#L85)
- Sai do modo do ncurses e devolve o terminal ao estado normal

### [`car.c`](car.c)

[`if (key == KEY_UP || key == 'w' || key == 'W')`](car.c#L95)
- `'w'` -> um carácter - char
- `"w"` -> uma string - char*

### [`game.c`](game.c)

[`mvprintw(11, 0, "Corrida Terminada! 🏁");`](game.c#L65)
- `mvaddstr()` -> trabalha com wide caracters
- `mvprintw()` -> trabalha com strings normais

### [`track.h`](track.h)

[`extern char track[9][14];`](track.h#L4)
- `extern` -> track existe, mas está definido em outro ficheiro

[`timer.h`](timer.h)

[`double get_time_ms(void);`](timer.h#L4)
- `double` -> tipo numérico utilizado para representar números com casas decimais e maior precisão do que `float`
