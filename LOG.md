# LOG

## Sessão 1 - 20/08/2026 - 16:00 - 17:30

**Funcionalidades implementadas:**
- Preparação da estrutura inicial do projeto e configuração do ambiente de desenvolvimento.
- Criados os ficheiros principais, incluindo `main.c`, `game.c`, `game.h`, `track.c`, `track.h`, `README.md`, `LOG.md` e `Makefile`.
- Configuração do `ncurse` e do `Makefile`.

**Maior dificuldade:**
- Configuração da biblioteca `ncurses` no ambiente UCRT64 do MSYS2. 
- O VS Code não reconhecia inicialmente o ficheiro `ncurse.h` e a compilação apresentava problemas na ligação da biblioteca.

**Como resolvi:**
- Verifique a instalação através do `pacman`, localizei os ficheiros `ncurses` e testei a compilação manualmente com `gcc`, utilizando o caminho do header e a biblioteca `ncursesw`. Por fim, configurei o IntelliSense do VS Code para reconhecer o diretório do `ncurses`.

**Próximo passo planeado:**
- Começar a implementação da pista e testar a sua representação no terminal através do `ncurses`.

**Linhas de código escritas hoje (estimativa):** ~0

### Recursos consultados:
- MSYS2 - gestão de pacotes e ambiente UCRT64.
- GNU ncurses - biblioteca utilizada para a interface do jogo.
- GNU Make - ferramenta utilizada para automatizar a compilação.
- Documentação/configuração do IntelliSense da extensão C/C++ do VS Code.

### Comandos/testes utilizados:
- `pacman -Qs ncurses`
- `pacman -Ql mingw-w64-ucrt-x86_64-ncurses | grep ncurses.h`
- `ls /ucrt64/lib/libncurses*`
- `gcc teste.c -I/ucrt64/include/ncurses -lncursesw -o teste`

## Sessão 2 - 20/08/2026 - 19:30 - 20:00

**Funcionalidades implementadas:**
- Criada a representação da pista através de uma matriz de caracteres e implementada a função `draw_track()` para desenhá-lo no terminal.
- Configurado o `main.c`para inicializar o `ncurses`.
- Criados ficheiros `car.c`e `car.h`, definida uma posição inicial para o carro e implementada a função `draw_car()`.

**Maior dificuldade:**
- Compreender a utilização do `ncurses`para desenhar elementos em posições específicas do terminal e integrar os diferentes ficheiros do projeto através do `Makefil`.

**Como resolvi:**
- Utilizei `mvprintw()` para posicionar os elementos no terminal e organizei e implementação da pista e do carro em ficheiros separados. O `main.c`ficou responsável por inicializar o `ncurses`e chamar as funções necessárias.

**Próximo passo planeado:**
- Corrigir a posição inicial do carro para que fique sobre a pista e implementar o movimento através das teclas direcionais.

**Linhas de código escritas hoje (estimativa):** ~62

### Recursos consultados:
- Documentação da biblioteca `ncurses`.
- Documentação do `mvprintw()`e das funções de inicialização/terminação do `ncurses`.

## Sessão 3 - 21/08/2026 - 09:00 - 10:00

**Funcionalidades implementadas:**
- Corrigida a posição inicial do carro para que fique sobre a pista.
- Implementado o movimento do carro através  das teclas direcionais (↑, ↓, ←, →).
- Configurado o `ncurses`para reconhecer as teclas direcionais e criado o ciclo de jogo para atualizar a posição e redesenhar a pista e o carro.

**Maior dificuldade:**
- Implementar o movimento contínuo do carro através das teclas direcionais e criada a função `move_car()`para atualizar as coordenadas do carro de acordo com a tecla pressionada.
- O `main.c` passou a utilizar um ciclo para ler as teclas e atualziar o jogo.

**Próximo passo planeado:**
- Impedir que o carro saia da pista, verificando a posição para a qual pretende mover-se corresponde a uma posição válida da pista.

**Linhas de código escritas hoje (estimativa):** ~48

### Recursos consultados:
- Documentação da biblioteca `ncurses`.
- Documentação de `keypad()`e das constantes `KEY_UP`, `KEY_DOWN`, `KEY_LEFT`e `KEY_RIGHT`.
- Documentação de `getch()` para leitura das teclas.
