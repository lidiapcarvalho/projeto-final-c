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
- Compreender a utilização do `ncurses`para desenhar elementos em posições específicas do terminal e integrar os diferentes ficheiros do projeto através do `Makefile`.

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
- A posição foi válida através da matriz da pista, permitindo o movimento apenas sobre `#`(pista) ou `=`(linha da meta).
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

## Sessão 8 - 24/08/2026 - 11:00 - 16:00

**Funcionalidades implementadas:**
- Separação entre direção e movimento do carro.
- Implementação de `change_direction()` para alterar a direção através das teclas.
- Implementação do **movimento automático** do carro. O carro passou a continuar a deslocar-se na direção escolhida sem ser necessário manter a tecla pressionada.
- Ligação da velocidade ao intervalo entre movimentos através de `get_speed_delay()`.
- Introdução da medição de tempo com `clock()`, `clock_t`, `CLOCKS_PER_SEC` e `elapsed_time`.
- Teste dos diferentes intervalos associados às velocidades de 100, 200 e 300 km/h.
- Confirmado que `get_speed_delay()` devolve corretamente 300 ms, 200 ms e 100 ms respetivamente.

**Maior dificuldade:**
- Fazer o movimento automático funcionar independentemente da pressão das teclas.
- Compreender a diferença entre a leitura das teclas e o movimento do carro.
- Resolver a medição do tempo para controlar corretamente a velocidade.
- Identificar o motivo pelo qual o terminal apresentava um efeito de "tremor".

**Como resolvi:**
- Separei a alteração da direção (`change_direction()`) do movimento (`move_car()`).
- Passei a controlar o movimento através do tempo decorrido.
- Utilizei temporariamente `clock()` para estudar e testar a lógico de temporização.
- Comentei temporariamente `clear()` e confirmei que este era responsável pelo efeito visual de tremor.
- Testei os valores devolvidos por `get_speed_delay()` para confirmar que a lógica da velocidade estava correta.

**Testes realizados:**
- Movimento automático sem pressionar continuamente as teclas.
- Mudança de direção durante o movimento automático.
- Velocidades de 100, 200 e 300 km/h.
- Verificação dos valores de `get_speed_delay()`.
- Teste do `elapsed_time`.
- Teste com `clear()` comentado para identificar a origem do tremor do terminal.

**Próximo passo planeado:**
- Substituir `clock()` por uma solução de medição de tempo real decorrido, mantendo a compatibilidade entre diferentes sistemas operativos.
- Depois corrigir o redesenho do terminal para eliminar o tremor sem deixar o `clear()` permanentemente desativado.
- Continuar o desenvolvimento da mecânica de velocidade e movimento automático.

**Linhas de código escritas na sessão (estimativa):** 53

## Sessão 9 - 24/08/2026 - 17:15 - 19:15

**Funcionalidades implementadas:**
- Investigação da utilização de `clock()` para controlo do tempo do movimento automático.
- Teste de `clock_gettime()` com `CLOCK_MONOTONIC`.
- Criação de `timer.h` e `timer.c` para separar a medição do tempo da lógica principal do jogo.
- Criação de um ficheiro de teste para verificar a nova função `get_time_ms()`.

**Maior dificuldade:**
- Perceber que `clock()` não era a solução mais adequada para medir tempo real decorrido.
- Resolver problemas de compilação e criação do executável no ambiente Windows/MSYS2.

**Como resolvi:**
- Testei `clock_gettime()` e confirmei que o ambiente suporta `CLOCK_MONOTONIC`.
Separei a funcionalidade de medição do tempo num módulo próprio.
Confirmei que `timer.c` e `teste.c` compilam individualmente com `gcc -c`.

**Testes realizados:**
- Teste de `clock_gettime()` com `CLOCK_MONOTONIC`.
- Verificação dos valores de `get_speed_delay()` para 100, 200 e 300 km/h.
- Compilação de `timer.c` e `teste.c` em ficheiros objeto.
- Tentativa de criação do executável, que resultou em `Permission denied`.

**Próximo passo planeado:**
- Resolver o problema de criação do executável no MSYS2.
- Testar `get_time_ms()`.
- Substituir a utilização de `clock()` no `main.c` pela nova função de medição de tempo.

**Linhas de código escritas na sessão (estimativa):** 22

## Sessão 10 - 25/08/2026 - 15:30 - 19:30

**Funcionalidades implementadas:**
- Integração dos ficheiros `timer.c` e `timer.h` no `Makefile`.
- Substituição do sistema baseado em `clock()` por `get_time_ms()`.
- Implementação cronómetro da corrida em segundos.
- Criação da variável `race_started` para controlar o estado da corrida.
- Definição da tecla **Enter** como início da corrida.
- Impedimento do movimento do carro antes do início da corrida.
- Criação da função `start_race()` para preparar a sequência de partida.
- Implementação inicial da mensagem `PREPARE-SE!`.
- Testes das velocidades de 100, 200 e 300 km/h.
- Testes das voltas e do funcionamento do croómetro.

**Maior dificuldade:**
- Resolver o erro `Permission denied` ao tentar executar os progrmas de teste.
- Distinguir o tempo decorrido entre movimentos (`elapsed_time`) do tempo total da corrida (`race_time`).
- Integrar o novo sistema de temporização no `main.c` sem interferir com a lógica de movimento.

**Como resolvi:**
- Foi identificado que o `Permission denied` era causado pelo AVG, que detetava os executáveis de teste como uma ameaça heurística e os movia para a quarentena.
- Foi criado o módulo `timer.c`/`timer.h`, permitindo centralizar a obtenção do tempo através de `get_time_ms()`.
- Foram utilizados temporizadores independentes para controlar o intervalo de movimento e a duração total da corrida.
- Foi criado o estado `race_started`, permitindo separar o período anterior à partida da corrida propriamente dita.

**Observações:**
- A velocidade influencia corretamente a frequência do movimento.
- O carro permanece parado antes de carregar em Enter.
- O cronómetro começa no momento da partida.
- As voltas continuam a ser contabilizadas corretamente.
- O terminal permanece estável durante a execução.
- Ficou iniciada a implementação de uma sequência de partida inspirada na F1, a desenvolver na próxima sessão.

**Próximo passo planeado:**
- Implementação da sequência de partida estilo F1.
- Correção e revisão da apresentação do tempo da corrida.
- Revisão do comportamento no final da corrida.
- Testes gerais do funcionamento do jogo.
- Implementação do menu principal e das instruções.
- Revisão da qualidade e organização do código.
- Revisão e conclusão do `apontamentos.md`, incluindo a verificação das referências aos ficheiros e linhas de código.
- Atualização final da documentação e realização dos testes finais.

**Linhas de código escritas na sessão (estimativa):** 53

## Sessão 11 - 26/08/2026 - 15:25 - 20:00

**Funcionalidades implementadas:**
- Sistema de cores com `ncurses`.
- Criação de luzes de partida com cinco posições, onde acendem progressivamente a vermelho e apagam-se simultaneamente ao iniciar a corrida.
- Cronómetro sincronizado com o apagão das luzes.
- Circuito e informações da corrida deixaram de aparecer antes da partida.
- Remoção do `Delay` que estava a ser utilizado como informação de debug.
- Reorganização da posição visual da pista.
- Alinhamento do carro com a nova posição da pista.
- Separação entre as coordenadas da matriz da pista e as coordenadas visuais do terminal.

**Maior dificuldade:**
- Organizar os diferentes elementos no terminal sem que as luzes, pista, carro e informações se sobrepusessem.
- O carro passou a utilizar esse mesmo deslocamento apenas no momento de ser desenhado.
- As coordenadas internas da matriz permaneceram inalteradas, preservando a lógica de colisão e movimento.

**Teste realizados:**
- Compilação sem erros.
- Sistema de cores funcional.
- Sequência de cinco luzes e apagão das mesmas funcional.
- Cronómetro inícia no momento correto.
- Circuito só aparece depois da preparação.
- Carro mantém-se alinhado com a pista após a alteração de posição.
- Interface visual melhorada.

**Próximo passo planeado:**
- Reorganizar definitivmanete o `start_race()` para colocar `PREPARE-SE!` e as luzes acima da pista.
- Continuar polimento da interface.
- Rever a apresentação de fim de corrida.
- Eventualmente começar o **menu**.
- Mais à frente, se o tempo permitir, avaliar o histórico de voltas com as cores de conometragem F1.
- **Verificas as referências** do `apontamentos.md` antes da conclusão do projeto.

**Linhas de código escritas na sessão (estimativa):** 79

## Sessão 12 - 27/08/2026 - 15:30 - 19:50

**Funcionalidades implementadas:**
- Integração do menu principal no fluxo do jogo.
- Criação de um ciclo principal para permitir voltar ao menu após cada corrida.
- Possibilidade de iniciar uma nova corrida sem fechar o programa.
- Implementação do ecrã de resultados no final da corrida, que apresenta o número de voltas e o tempo final.
- Reinício correto do estada da corrida através de `init_game()` e do cronómetro em cada nova partida.
- Tratamento do buffer de entrada do `ncurses` com `flushinp()`.
- Correção da apresentação do menu após o término da corrida.
- Ajustes no `main.c`, `game.c`, `menu.c`, `menu.h`, `game.h`, `track.c`, `track.h`, `car.c` e `Makefile`.
- Testes sucessivos da corrida e do regresso ao menu.

**Maior dificuldade:**
- A principal difucldade foi reorganizar o fluxo do programa sem interferir com a lógica da corrida que já estava funcional.
- Distinção ente o ciclo principal do programa e do ciclo específico da corrida, permitindo que o jogo passasse de **menu → corrida → resultados → menu**.
- Também surgir um problema com o `ncurses`: ao regressar ao menu, uma tecla que permanecia no buffer de entrada podia ser intrepretada como uma nova opção. Este problema foi resolvido com `flushinp()` e com a alternância entre `nodelay()` e `timeout()` conforme o contexto.
- Outra dificuldade foi garantir que o estado da corrida era totalmente reiniciado. A variável `race_started()` permanecia ativa entre partidas, fazendo com que o cronómetro continuasse a contar. A inclusão de `race_started = 0` em `init_game()` resolveu o problema.

**Teste realizados:**
- Testado o início da corrida através do menu.
- Testado o abandono da corrida com `ESC`.
- Testado o regresso ao menu.
- Testada a opção de sair pelo menu.
- Testado o reinício de uma nova corrida.
- Confirmado que o cronómetro reinicia corretamente.
- Confirmado que o menu deixa de ficar sobreposto ao circuito.
- Confirmado o funcionamento do ecrã de resultados.
- Realizadas várias tentativas para testar o sistema de voltas e o cronómetro.

**Recorde 🏆:**
Durante os testes da sessão foi alcançado um novo melhor tempo: 26,43 segundos.

**Resultado da sessão:**
- O jogo passou a ter um fluxo mais completo e organizado, deixando de terminar obrigatoriamente após uma corrida. 
- O jogador pode iniciar uma partida, terminar a corrida, visualizar o resultado e regressar ao menu para jogar novamente.

**Próximo passo planeado:**
- Implementar o armazenamento do melhor tempo.
- Criar um histórico de tempos.
- Avaliar a aplicação das cores de cronometragem inspiradas na Fórmula 1.
- Melhorar visualmente o ecrã de resultados.

**Linhas de código escritas na sessão (estimativa):** 35

## Sessão 13 - 28/08/2026 - 09:00 - 12:30

**Funcionalidades implementadas:**
- Revisão do feedback do professor sobre a lógica da pista.
- Alteração do sistema de checkpoints, passando de coordenadas fixas para uma matriz própria de checkpoints.
- Revisão e compreensão do uso de `extern` para variáveis globais entre ficheiros.
- Revisão da função `clock_gettime()` e do relógio `CLOCK_MONOTONIC`, utilizado para medir intervalos de tempo.
- Criação dos módulos `history.c` e `history.h`.
- Implementação do armazenamento dos tempos das corridas.
- Criação de um histórico simples de corridas.
- Implementação de uma função recursiva para percorrer e apresentar o histórico.
- Adição da opção "Histórico" ao menu.
- Integração do histórico no fluxo principal do jogo.
- Testes de compilação e execução realizados com sucesso.

**Maior dificuldade:**
- A principal dificuldade foi reorganizar o sistema de checkpoints para deixar de depender diretamente das coordenadas da pista. 
- Foi criada uma matriz `checkpoints[]`, permitindo separar a localização dos sensores da lógica de contagem das voltas.
- Também foi necessário compreender melhor a utilização de `clock_gettime()` com `CLOCK_MONOTONIC` e distinguir a medição da duração da corrida do registo futuro da data e hora.

**Recursão:**
Foi implementada a função `draw_history_recursive()`, que percorre os tempos armazenados no histórico até atingir o número de corridas registadas. A função possui uma condição de paragem e chama-se novamente com o índice seguinte.

**Teste realizados:**
- `make` executado sem erros.
- Corrida completa realizada com sucesso.
- Tempo da corrida guardado corretamente.
- Histórico apresentado através do menu.
- Regresso ao menu após consultar o histórico confirmado.
- Reinício de novas corridas confirmado.

**Recorde 🏆:** 24,51 segundos

**Próximo passo planeado:**
- Completar os apontamentos sobre `clock_gettime()`, `CLOCK_MONOTONIC` e `struct timespec`.
- Evoluir o histórico para guardar data, hora e tempo das corridas de forma persistente.
- Atualizar o `README.md`.
- Implementar a componente visual dos setores e cores.

**Linhas de código escritas na sessão (estimativa):** 50

## Sessão 14 - 28/08/2026 - 12:45 - 21:15

**Funcionalidades implementadas:**
- Implementação de um sistema de histórico de corridas.
- Criação do ficheiro `historico.txt` para guardar os tempos das corridas.
- Registo da data e da hora de cada corrida.
- Atualização da função `save_race_time()` para guardar os dados da corrida no ficheiro.
- Criação das estruturas `race_dates[]` e `race_hours[]` para armazenar a data e a hora das corridas.
- Adaptação da função `load_history()` para carregar os dados do histórico.
- Atualização da apresentação do histórico para mostrar:
    - número da corrida;
    - data;
    - hora;
    - tempo da corrida.
- Implementação de uma função recursiva para apresentar as corridas do histórico.
- Limitação do histórico em memória a 10 corridas através de `MAX_RACES`.
- Integração do histórico no menu principal.

**Maior dificuldade:**
- A principal dificuldade da sessão foi a adaptação do histórico ao novo formato do ficheiro, que passou de guardar apenas o tempo para guardar data, hora e tempo.
- Durante os testes verificou-se um problema na leitura e apresentação de várias entradas do histórico, apesar de os dados estarem corretamente gravados no `historico.txt`. A situação ficou identificada, mas a correção definitiva ficará para a próxima sessão.

**Testes realizados:**
- Compilação realizada sem erros em várias etapas.
- Testada a gravação de várias corridas no historico.txt.
- Confirmado que o ficheiro mantém os registos com data, hora e tempo.
- Confirmada a apresentação de uma entrada do histórico no formato pretendido.
- Identificado um problema ainda pendente no carregamento/apresentação de todas as entradas do histórico.

**Resultado da sessão:**
- O sistema de histórico ficou parcialmente implementado e funcional na gravação dos dados, ficando pendente a correção do carregamento e apresentação consistente das várias corridas.
- Durante os testes foi também estabelecido um novo recorde pessoal de **24,39575 segundos**, melhorando o anterior de **24,51 segundos** em aproximadamente **0,11 segundos**. 🏆

**Próximo passo planeado:**
- Corrigir o carregamento das várias entradas do histórico.
- Confirmar a apresentação das 10 corridas.
- Melhorar visualmente o histórico com cores.
- Destacar o melhor tempo.
- Continuar a evolução visual do jogo.
- Atualizar os apontamentos técnicos relacionados com o histórico e a recursão.

**Linhas de código escritas na sessão (estimativa):** 74

## Sessão 15 - 29/08/2026 - 13:30 - 19:35

**Funcionalidades implementadas:**
- Criado a estrutura inicial do `README.md`.
- Documentadas as funcionalidades já implementadas no projeto.
- Documentado o sistema de medicação do tempo através de `clock_gettime()` e `CLOCK_MONOTONIC`.
- Documwntado o sistema de histórico de corrida.
- Corrigindo o carregamento de várias corridas a partir do `historico.txt`.
- Implementado o armazenamento das 10 corridas mais recentes em memória.
- Mantido o ficheiro `historico.txt` com histórico completo das corridas.
- Corrigida a apresentação das datas no histórico.
- Confirmado o funcionamento do histórico com data, hora e tempode corrida.

**Maior dificuldade:**
A principal dificuldade desta sessão foi corrigir o carregamento do histórico. 
Inicialmente, apenas a primeira corrida existente no ficheiro era apresentada. O problema estava relacionado com a leitura das linhas através de `fscanf()`, tendo sido necessário permitir que os espaços em branco e mudanças de linha fossem ignorados entre leituras.

Posteriormente, foi necessário adaptar o carregamento para que, quando existem mais de 10 corridas, sejam mantidas apenas as 10 mais reccentes. Durante esta alteração surgiram problemas na apresentação das datas, que foram corrigidis através da utilização de `strcpy()` para copiar corretamente os dados entre as posições dos arrays.

**Como resolvi:**
Comecei por adaptar o sistema de histórico para guardar, além do tempo a data e a hora de cada corrida. Durante os testes, detetei problemas na leitura e apresentação dos dados, nomeadamente na conversão dos tempos e na apresentação das últimas 10 corridas. 
- Analisei os valores armazenados no ficheiro `historico.txt` e ajustei o `load_history()` para ler corretamente cada campo e manter apenas as corridas mais recentes. 
- Após vários testes, confirmei que o histórico era carregado corretamente quando o programa era executado novamente. 

**Resultado da sessão:**
O sitema de histórico encontra-se funcional, apresentando as 10 corridas mais recentes data, hora e tempo. O ficheiro `historico.txt` continua a preservar todos os registos realizados.

O `README.md` encontra-se estruturado e parcialmente preenchido.

**Próximo passo planeado:**
- Melhorar a interface do jogo através da utilização de cores.
- Avaliar a utilização de cores para distinguir a pista, o carro, a linha de meta e outras informações relevantes.
- Continuar a desenvolver a componente visual do jogo.

**Linhas de código escritas na sessão (estimativa):** 52

## Sessão 16 - 29/08/2026 - 19:45 - 22:15

**Funcionalidades implementadas:**
- Aplicação de cores à interface do jogo:
    - vermelho para o carro;
    - verde para o melhor tempo;
    - amarelo para o tempo mais lento;
    - branco para os restantes tempos e para a pista.
- Implementação da identificação visual do melhor e do pior tempo no histórico.
- Adição de um resumo do melhor tempo e do tempo mais lento no histórico de corridas.
- Ajustes na apresentação da pista.
- Verificação da apresentação das últimas 10 corridas.
- Teste geral das funcionalidades do jogo após as alterações visuais.

**Maior dificuldade:**

A principal dificuldade esteve na implementação da identificação e apresentação dos melhores e piores tempos a partir dos valores carregados do histórico. Foi necessário corrigir a forma como os índices das corridas eram utilizados para associar cada tempo à respetiva cor.

**Como resolvi:**
- Para implementar as cores dos tempos, comecei por identificar o melhor e o pior valor do histórico. Durante os testes, as cores não estavam a ser aplicadas corretamente, pelo que utilizei valores de diagnóstico para verificar os dados armazenados no vetor `race_times`. 
- Percebi que a comparação direta dos valores não estava a funcionar como pretendido e alterei a lógica para guardar os índices correspondentes ao melhor e ao pior tempo. Esses índices passaram depois a ser utilizados na função recursiva para aplicar a cor correta a cada corrida. 
- Por fim, adicionei um resumo do melhor e do pior tempo e testei novamente todo o histórico.

**Testes realizados:**
- Compilação do projeto sem erros.
- Verificação das cores do carro e dos tempos.
- Verificação do cálculo do melhor e do pior tempo.
- Verificação da apresentação do histórico.
- Teste geral do jogo, confirmando que as funcionalidades existentes continuam a funcionar corretamente.

**Resultado da sessão:**
O jogo encontra-se funcional e com a interface visual definida. As principais funcionalidades previstas estão implementadas e testadas.

**Próximo passo planeado:**
- Rever os apontamentos do projeto.
- Rever e completar o `README.md`.
- Fazer uma revisão final do código e da documentação.
- Realizar os testes finais antes da entrega.

**Linhas de código escritas na sessão (estimativa):** 69
