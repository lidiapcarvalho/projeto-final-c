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

**Linhas de código escritas na sessão (estimativa):** 0

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

**Linhas de código escritas na sessão (estimativa):** 62

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

**Linhas de código escritas na sessão (estimativa):** 48

### Recursos consultados:
- Documentação da biblioteca `ncurses`.
- Documentação de `keypad()`e das constantes `KEY_UP`, `KEY_DOWN`, `KEY_LEFT`e `KEY_RIGHT`.
- Documentação de `getch()` para leitura das teclas.

## Sessão 4 - 21/08/2026 - 10:30 - 12:15

**Funcionalidades implementadas:**
- Implementada a deteção da pista, impedindo o carro de atravessar as zonas fora da pista.
- Adicionada a verificação dos limites de matriz para evitar acessos fora do seus limites.
- Implementada uma tecla de saída (`Q/q`) para terminar o jogo corretamente.

**Maior dificuldade:**
- Fazer o carro verificar a posição seguintes antes de se mover e resolver o problema causado pelo acesso a posições e fora da matriz.
- Também foi necessário implementar uma forma controlada de terminar o programa, uma vez que o `while` mantinha o jogo em execução.

**Como resolvi:**
- Foram calculados as novas coordenadas do carro antes de alterar a sua posição.
- A posição foi válida através da matriz da pista, permitindo o movimento apenas sobre `#`ou `=`.
- Foi também adicionada uma verificação dos limites da matriz e uma condição para sair do ciclo através da tecla `Q/q`.

**Próximo passo planeado:**
- Implementar o sistema de voltas e a linha de partida/chegada.

**Linhas de código escritas na sessão (estimativa):** 38

## Sessão 5 - 21/08/2026 - 15:45 - 20:15

**Funcionalidades implementadas:**
- Iniciada a implementação do sistema de voltas. 
- Foi criado o estado da corrida no `game.c`, incluindo o contador de voltas e o sistema de checkpoint. 
- Implementado o primeiro checkpoint na posição `(0,5)` e ajustada a lógica de deteção da linha de partida/chegada.

**Maior dificuldade:**
- A primeira implementação permitia que o contador de voltas aumentasse incorretamente, incluindo várias voltas sem o carro completar o percurso. 
- Foi necessário rever a lógica de `crossed_finish` e perceber que o checkpoint precisava de ser utilizado como condição para validar uma volta.

**Como resolvi:**
- O contador passou a exigir que o carro saia da linha de partida/chegada, passe pelo checkpoint e só depois volte à linha de chegada para completar uma volta. 
- A variável `checkpoint` passou a controlar se o percurso necessário foi realizado antes de incrementar `lap`.

**Testes realizados:** 
- Confirmado que voltar diretamente à linha de chegada sem passar pelo checkpoint não incrementa a volta. 
- Confirmado também que permanecer ou movimentar-se junto à linha de chegada não provoca múltiplas contagens.

**Próximo passo planeado:** 
- Implementar um segundo checkpoint, aproximadamente na posição `(4,10)`, para tornar a validação da volta mais robusta.

**Linhas de código escritas na sessão (estimativa):** 68

## Sessão 6 - 22/08/2026 - 21:00 - 23:00

**Funcionalidades implementadas:**
- Implementação dos restantes checkpoints para validar o percurso da corrida e impedir que as voltas fossem contabilizadas sem o carro completar o circuito.
- Os checkpoints ficaram definidos pela ordem do percurso: `(6,0)`, `(0,5)`e `(4,10)`.
- Implementado também o sistema de deteção do final da corrida após 3 voltas.

**Maior dificuldade:**
- A ordem inicial dos checkpoints não correspondia ao percurso real da pista, fazendo com que o carro nunca conseguisse completar uma volta.
- Foi necessário analisar o percurso e reorganizar os checkpoints.
- Também houve problemas relacionados com apresentação da mensagem de fim de corrida através do `ncurses`.

**Como resolvi:**
- Os checkpoints passaram a funcionar como estados sequenciais `(0 → 1 → 2 → 3)`, sendo necessário passar por cada um na ordem correta antes de a volta ser contabilizada. 
- Foi criada a variável race_finished, que é ativada quando o contador chega às 3 voltas. 
- A mensagem de fim da corrida passou a ser apresentada antes de o programa terminar.

**Testes realizados:** 
- Confirmado que as três voltas são contabilizadas corretamente apenas quando os três checkpoints são percorridos pela ordem definida.
- Confirmado também que, após a terceira volta, a corrida termina e é apresentada a mensagem de finalização.

**Outros problemas resolvidos:**
- Foi corrigido um problema de configuração do ambiente de desenvolvimento relacionado com o reconhecimento do `ncurses`. 
- Foram também analisadas questões relacionadas com `setlocale`, `ncursesw` e caracteres Unicode na tentativa de apresentar o emoji de bandeira na mensagem final.

**Próximo passo planeado:** 
- Continuar o desenvolvimento das mecânicas da corrida, nomeadamente a implementação da velocidade do carro.

**Linhas de código escritas na sessão (estimativa):** 55

## Sessão 7 - 23/08/2026 - 17:00 - 19:15

**Funcionalidades implementadas:**
- Implementação da variável `speed`, com valores de 1 a 3, correspondentes a 100, 200 e 300 km/h.
- Criação da função `change_speed()` com limites mínimo e máximo.
- Criação da função `get_speed_delay()` para relacionar a velocidade com o intervalo de tempo.
- Implementação dos controlos de velocidade:
    -> Jogador 1: `Q` para acelerar e `E` para travar;
    -> Jogador 1: `+` para acelerar e `-` para travar.
- Implementação das teclas `W/A/S/D`como alternativa às setas para controlar a direção.
- Alteração da tecla de saída de `Q/q` para `ESC`.
- Introdução do `timeout()` para permitir que o jogo continue a executar sem ficar bloquado à espera de uma tecla.
- Criação da variável `direction` para guardar a direção atual do carro.
- Inicialização da direção com `KEY_UP`.

**Maior dificuldade:**
- Encontrar uma forma adequada de implementar os controlos de velocidade sem os misturar com as teclas de direção.
- Perceber o funcionamento do `timeout()` e do `ERR` devolvido pelo `getch()`.
- Encontrar teclas adequadas para o segundo jogador, uma vez que `Shift` e `Ctrl` não funcionaram como esperado no `ncurses`.

**Como resolvi:**
- Separei os controlos de direção dos controlos de velocidade.
- Mantive `W/A/S/D` e as setas exclusivamente para a direção.
- Criei limites para impedir que a velocidade ultrapasse 300 km/h ou deças abaixo de 100 kmh.
- Usei `timeout()` para recuperar o jogo para funcionar continuamente, mesmo sem entrada do jogador.
- Criei `direction` para preparar a implementação do movimento automático.

**Testes realizados:**
- Teste das teclas `W/A/S/D` e das setas.
- Teste da acelaração e travagem com `Q/E` e `+/-`.
- Verificação dos limites de velocidade entre 100 a 300 km/h.
- Teste de `ESC` para sair do jogo.
- Compilação realizada sem erros.

**Próximo passo planeado:**
- Implementar o movimento automático do carro com base na direção e na velocidade.
- Fazer com que a velocidade tenha impacto real na movimentação do carro.

**Linhas de código escritas na sessão (estimativa):** 74
