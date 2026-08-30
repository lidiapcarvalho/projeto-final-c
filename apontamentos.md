## Caderno de Apontamentos

> Registo dos principais conceitos, funções e soluções explorados ao longo do desenvolvimento do projeto, com referências diretas ao código para facilitar a consulta.

### [`main.c`](main.c)

[`#include <locale.h>`](main.c#L5)
- localização/regionalização do programa (locale)

[`setlocale(LC_ALL, "");`](main.c#L15)
- Diz ao C, para usar as definições de idioma/codificação que o sistema operativo está a usar
- `setlocale()` -> configura o lacale do programa
- `LC_ALL` -> aplica a configuração a todas as categorias do locale
- `""` -> pede ao programa para usar o locale definido pelo ambiente/sistema operativo

[`initscr();`](main.c#L17)
- Inicializa o ncurses

[`init_pair(1, COLOR_RED, COLOR_BLACK);`](main.c#L20)
- Par de cor nº 1, texto vermelho, fundo preto

[`flushinp();`](main.c#L32)
- Ela limpa o buffer de entrada do terminal
- Neste contexto, ao limpar as teclas pendentes no buffer de entrada, evita que a tecla `ENTER` da corrida anterior seja lida como opção do menu

[`keypad(stdscr, TRUE);`](main.c#L54)
- Permite ao ncurses reconhecer corretamente teclas especiais, como as setas

[`double last_move = get_time_ms();`](main.c#L61) 
- `get_time_ms()` -> função criada no projeto para obter o tempo atual através do relógio monotónico e devolvê-lo em milissegundos.
- Neste caso, o valor devolvido é guardado na variável last_move e representa o momento em que foi registado o último movimento do carro.
- Este valor é posteriormente utilizado para calcular quanto tempo passou desde o último movimento e determinar se já passou o intervalo necessário para o carro se poder mover novamente.

[`key = getch();`](main.c#L84)
- Faz o programa esperar por uma tecla
- Sem isto, o programa poderia desenhar a pista e terminar imediatamente

[`if (key != ERR)`](main.c#L120)
- ERR -> constante do ncurses que significa, neste contexto, "não foi recebida nenhuma tecla"

[`endwin()`](main.c#L143)
- Sai do modo do ncurses e devolve o terminal ao estado normal

**Usado temporariamente:**

`clock_t last_move = clock();`
- `clock_t` -> tipo de dado usado para guardar um valor produzido por clock()
- `clock()` -> devolve um valor que representa tempo de CPU utilizado pelo programa desde que começou

Diferenças comparativamente a double last_move = get_time_ms();
- clock() -> dependíamos do relógio do CPU
- get_time_ms() -> usamos o nosso temporizador baseado em tempo monotónico

`clear();`
- Limpa o ecrã antes de desenharmos novamente

### [`car.c`](car.c)

[`if (key == KEY_UP || key == 'w' || key == 'W')`](car.c#L99)
- `'w'` -> um carácter - char
- `"w"` -> uma string - char*

### [`game.c`](game.c)

[`attron(COLOR_PAIR(2) | A_BOLD);`](game.c#L31)
- `A_BOLD` -> deixa a apresentação a negrito

[`mvprintw(11, 0, "Corrida Terminada! 🏁");`](game.c#L101)
- `mvaddstr()` -> trabalha com wide caracters
- `mvprintw()` -> trabalha com strings normais

### [`track.h`](track.h)

[`extern char track[9][14];`](track.h#L4)
- `extern` -> track existe, mas está definido em outro ficheiro

### [`timer.h`](timer.h)

[`double get_time_ms(void);`](timer.h#L4)
- `double` -> tipo numérico utilizado para representar números com casas decimais e maior precisão do que `float`

### [`timer.c`](timer.c)

[`struct timespec tempo;`](timer.c#L6)
- Cria uma variável que consegue guardar o tempo em duas partes

[`clock_gettime(CLOCK_MONOTONIC, &tempo);`](timer.c#L8)
- Obtém o tempo através de um relógio monotónico, adequado para medir intervalos de tempo, pois não depende da hora do sistema e não deve andar para trás.

[`return (double)tempo.tv_sec * 1000.0 + (double)tempo.tv_nsec / 1000000.0;`](timer.c#L10-11)
- `tv_sec` -> segundos, daí multiplicarmos por 1 000 para converter para milissegundos
- `tv_nsec` -> nanosegundos, dividimos por 1 000 000 para converter para milissegundos

Estes dois valores são depois somados, por forma a obter uma única medida de tempo (no caso, milissegundos)

- `double` -> permite guardar também a parte decimal dos milissegundos, permitindo obter valores como 24510.5 ms, que depois podem ser apresentados como 24.51 s.

Porquê `CLOCK_MONOTONIC`?

Neste projeto não precisamos de saber a hora atual, mas sim **quanto tempo passou entre dois acontecimentos**.

O `CLOCK_MONOTONIC` é adequado para este objetivo porque é um relógio, concebido para medir intervalos de tempo e que não depende da alteração da hora do sistema.

Por exemplo:
- início da corrida -> regista o instante inicial;
- fim da corrida -> regista o instante final;
- diferença entre os dois -> duranção da corrida.

Também é utilizado para controlar os atrasos associados ao movimento do carro.

**Diferenças entre os relógios utilizados:**
- `CLOCK_MONOTONIC` -> utilizado para medir durações
- `time()` + `localtime()` -> utilizados para saber quando uma corrida aconteceu, permitindo guardar a data e a hora no histórico

Assim, cada mecanismo tem uma função diferente no projeto: um mede quanto tempo durou a corrida e o outro regista quando aconteceu.

## [`history.c`](history.c)

[`FILE *ficheiro = fopen("historico.txt", "a");`](history.c#L30)
- `"a"` -> append

[`FILE *ficheiro = fopen("historico.txt", "r");`](history.c#L115)
- `"r"` -> abre o ficheiro para leitura

[`if (fscanf(ficheiro, " %10[^;];%5[^;];%29[^\n]",`](history.c#L129)
- `fscanf` -> lê os valores do ficheiro
- `[^;]` -> é um scanset, que significa: "lê caracteres enquanto eles não forem ;". O '^' significa negação.

### Nota de autor:
O código contém comandos/estruturas previamente preparados para uma possível implementação de um modo multiplayer. Esta funcionalidade não faz parte da versão atual do jogo, mas a estrutura permite que possa ser desenvolvida futuramente.
