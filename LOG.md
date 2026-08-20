# LOG

## Sessão 1 - 20/08/2026

**Funcionalidades implementadas:**
- Preparação da estrutura inicial do projeto e configuração do ambiente de desenvolvimento.
- Criados os ficheiros principais e configurado o `ncurse` e o `Makefile`.

**Maior dificuldade:**
- Configuração do `ncurses` no ambiente UCRT64 e ligação da biblioteca ao compilador.

**Como resolvi:**
- Verifique a instalação através do `pacman`, localizei os ficheiros `ncurses` e testei a compilação com `gcc`, utilizando o caminho do header e a biblioteca `ncursesw`.

**Próximo passo planeado:**
- Começar a implementação da pista e testar a sua representação no terminal através do `ncurses`.

**Linhas de código escritas hoje (estimativa):** ~0

### Recursos consultados:
- [MSYS2] (https://www.msys2.org/)
- [GNU ncurses] (https://invisible-island.net/ncurses/)
- [GNU Make] (https://www.gnu.org/software/make/)

### Comandos/testes utilizados:
- `pacman -Qs ncurses`
- `pacman -Ql mingw-w64-ucrt-x86_64-ncurses | grep ncurses.h`
- `gcc teste.c -I/ucrt64/include/ncurses -lncursesw -o teste`
