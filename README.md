# 🏎️ Corrida - Jogo de Corrida em C

## 📖 Descrição

Este projeto consiste no desenvolvimento de um jogo de corrida em modo texto, programado em linguagem C e utilizando a biblioteca `ncurses` para a interface no terminal.

O jogador controla um carro numa pista representada através de uma matriz, devendo completar três voltas no menor tempo possível. O jogo inclui um sistema de controlo do tempo, deteção de voltas através de checkpoints, registo dos tempos das corridas e um histórico persistente.

## 🎯 Objetivo do jogo

O objetivo é completar três voltas ao circuito no menor tempo possível.

Para que uma volta seja validada, o jogador deve passar pelos checkpoints definidos ao longo da pista antes de atravessar novamente a linha de chegada.

No final das três voltas, o tempo total da corrida é apresentado e guardado no histórico.

## 🎮 Como jogar

> Ao iniciar o programa, é apresentado um menu principal onde o jogador pode escolher entre iniciar uma corrida, consultar o histórico de corridas ou sair do programa.

Durante a corrida, o jogador controla o carro através das teclas direcionais.

### Controlos

| **Tecla** | **Ação**                      |
| --------- | ----------------------------- |
| `↑`       | Mover o carro para cima       |
| `↓`       | Mover o carro para baixo      |
| `→`       | Mover o carro para a direita  |
| `←`       | Mover o carro para a esquerda |
| `ESC`     | Sair / Interromper a corrida  |

### Regras

- A corrida é composta por 3 voltas.
- O carro só pode deslocar-se pelas posições consideradas válidas da pista.
- Os checkpoints têm de ser percorridos pela ordem definida.
- Uma volta só é contabilizada quando os checkpoints necessários foram completados e o carro atravessa a linha da meta.
- O tempo da corrida é medido desde o início até à conclusão das três voltas.
- No final da corrida, o tempo é apresentado e guardado no histórico.

## 🗺️ A pista

A pista é representada através de uma matriz de caracteres.

Cada posição da matriz corresponde a uma posição possível do circuito. O carácter `#` representa a estrada da pista, enquanto `=` representa a linha da meta/chegada.

O circuito é desenhado no terminal através da biblioteca `ncurses`.

### Sistema de voltas e checkpoints

Para evitar que uma volta seja contabilizada apenas por atravessar a linha da meta, foram definidos checkpoints intermédios.

Os checkpoints funcionam como pontos de validação da volta: o jogador deve passar pelos checkpoints na ordem correta antes de atravessar novamente a linha da meta.

Este sistema foi inspirado no funcionamento dos setores de uma pista de Fórmula 1, onde a passagem por diferentes pontos do circuito permite acompanhar e validar a posição do carro.

## ⏱️ Sistema de tempo

O tempo de cada corrida é medido desde o início da corrida até à conclusão das três voltas.

Para medir o tempo foi utilizada a função `clock_gettime()` com o relógio monotónico `CLOCK_MONOTONIC`. Este relógio é adequado para medir intervalos de tempo, uma vez que não é afetado por alterações à data ou à hora do sistema durante a execução do programa.

A função `get_time_ms()` obtém o tempo através de duas componentes:
- `tv_sec` - número de segundos;
- `tv_nsec` - número de nanossegundos.

Estes valores são convertidos para milissegundos, permitindo calcular a duração da corrida com precisão.

O tempo inicial é registado no início da corrida e, quando as três voltas são concluídas, é calculada a diferença entre o tempo final e o tempo inicial.

O resultado é posteriormente convertido de milissegundos para segundos e apresentado com duas casas decimais.

### Controlo da velocidade

A velocidade do carro também influencia o intervalo entre movimentos. O atraso utilizado entre movimentos é ajustado através da função `get_speed_delay()`, permitindo que diferentes velocidades correspondam a diferentes tempos de espera.

Desta forma, o movimento do carro e o sistema de medição do tempo funcionam em conjunto durante a corrida.

## 📊 Histórico de corridas

O jogo possui um sistema de histórico que permite guardar e consultar os tempos das corridas realizadas.

No final de cada corrida, são guardados no ficheiro [`historico.txt`](historixo.txt):
- a data da corrida;
- a hora da corrida;
- o tempo total obtido.

O ficheiro utiliza o seguinte formato:

data;hora;tempo

Por exemplo:

28/08/2026;20:33;24395,75

Os tempos são guardados em milissegundos e apresentados no jogo em segundos, com duas casas decimais.

O histórico é carregado a partir do ficheiro quando o programa é executado, permitindo manter os resultados entre diferentes utilizações do jogo.

Como o número de corridas mantidas em memória está limitado através da constante `MAX_RACES`, definida com o valor 10, são apresentadas no jogo apenas as 10 corridas mais recentes. Quando é adicionada uma nova corrida e já existem 10 registos em memória, o registo mais antigo é substituído.

Para a apresentação dos resultado foi implementada uma função recursiva, `draw_history_recursive()`, que percorre os registos do histórico e apresenta cada corrida no ecrã.

### Apresentação

Cada registo é apresentado com o número da corrida, a data, a hora e o respetivo tempo:

Corrida 1 | 28/08/2026 | 18:59 | 32,00 s
Corrida 2 | 28/08/2026 | 20:17 | 26,85 s

O histórico apresenta também:
- **Melhor tempo de sempre** — corresponde ao menor tempo encontrado em todo o ficheiro de histórico, mesmo que essa corrida já não esteja entre as 10 corridas apresentadas.
- **Tempo mais lento** — corresponde ao maior tempo entre as 10 corridas atualmente apresentadas.

Na interface, o melhor tempo é apresentado a verde, o tempo mais lento a amarelo e os restantes tempos a branco.

Desta forma, o sistema permite acompanhar a evolução das corridas recentes e manter o recorde pessoal obtido ao longo da utilização do jogo.

## 🎨 Interface

A interface do jogo é apresentada em modo texto através da biblioteca ncurses.

Foram utilizadas diferentes cores para facilitar a leitura das informações apresentadas ao jogador:

🔴 Vermelho — carro durante a corrida.
🟢 Verde — melhor tempo de sempre.
🟡 Amarelo — tempo mais lento entre as 10 corridas apresentadas.
⚪ Branco — restantes tempos e elementos da pista.

A utilização de cores permite distinguir rapidamente os diferentes tipos de informação sem alterar o funcionamento do jogo.

## 📁 Estrutura do projeto

O projeto está organizado em vários ficheiros, de forma a separar as diferentes responsabilidades do jogo.
| **Ficheiro**      | **Responsabilidade**                                                                                                                 |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| `main.c`          | Função principal do programa e gestão do fluxo geral do jogo e do menu.                                                              |
| `game.c`          | Gestão da lógica principal da corrida, incluindo voltas, checkpoints, início e fim da corrida e apresentação dos resultados.         |
| `game.h`          | Declaração das funções e variáveis públicas relacionadas com a lógica do jogo.                                                       |
| `track.c`         | Definição e desenho da pista.                                                                                                        |
| `track.h`         | Declarações relacionadas com a pista.                                                                                                |
| `car.c`           | Gestão da posição e do movimento do carro.                                                                                           |
| `car.h`           | Declarações relacionadas com o carro.                                                                                                |
| `timer.c`         | Medição do tempo da corrida e cálculo dos atrasos associados à velocidade.                                                           |
| `timer.h`         | Declarações relacionadas com o sistema de tempo.                                                                                     |
| `menu.c`          | Implementação e apresentação do menu principal.                                                                                      |
| `menu.h`          | Declarações relacionadas com o menu.                                                                                                 |
| `history.c`       | Gestão de histórico de corridas, incluindo gravação, carregamento e apresentação dos resultados.                                      |
| `history.h`       | Declarações relacionadas com o histórico.                                                                                            |   
| `historico.txt`   | Ficheiro utilizado para guardar os resultados das corridas entre diferentes execuções do programa.                                   |
| `Makefile`        | Automatização da compilação e ligação dos diferentes ficheiros do projeto.                                                           |
| `README.md`       | Documentação do projeto, incluindo o funcionamento, estrutura, utilização e referências.                                             |
| `LOG.md`          | Registo do desenvolvimento do projeto, das funcionalidades implementadas, dificuldades e alterações realizadas ao longo das sessões. |
| `apontamentos.md` | Registo de notas técnicas, explicações e aprendizagens realizadas durante o desenvolvimento do projeto.                              |


## 🧠 Conceitos de programação utilizados

Durante o desenvolvimento do projeto foram utilizados vários conceitos de programação em linguagem C:
- Variáveis e constantes;
- Tipos de dados (`int`, `double`, `char`);
- Estruturas de controlo (`if`, `else`, `while`, `for`);
- Funções e passagem de parâmetros;
- Vetores e matrizes;
- Ponteiros;
- Recursividade;
- Leitura e escrita de ficheiros;
- Manipulação de strings;
- Estruturas (`struct timespec`);
- Gestão do tempo;
- Utilização de bibliotecas externas;
- Sistema de cores e controlo do terminal através de `ncurses`.

## 🛠️ Tecnologias utilizadas

- Linguagem: C
- Biblioteca: `ncurses`
- Compilador: GCC
- Sistema de compilação: Make / `Makefile`
- Ambiente: MSYS2 UCRT64
- Controlo de versões: Git / GitHub

## ▶️ Compilação e execução

Para compilar o projeto, utilizar:

make

Depois da compilação, executar o programa através do ficheiro gerado:

./corrida.exe

O projeto necessita de um ambiente com suporte para a biblioteca `ncurses` e para o compilador GCC.

## 📚 Bibliografia e referências

Durante o desenvolvimento do projeto foram consultadas as seguintes referências:
- Documentação da linguagem C e das funções da biblioteca padrão;
- Documentação da biblioteca `ncurses`, utilizada para a interface em modo texto;
- Documentação da função `clock_gettime()` e do `CLOCK_MONOTONIC`, utilizados para a medição do tempo;
- Materiais e exercícios disponibilizados no âmbito da unidade curricular.

## 🚧 Melhorias futuras

Apesar de o jogo se encontrar funcional, existem algumas melhorias que poderiam ser implementadas futuramente:
- Adicionar mais pistas ou circuitos;
- Permitir diferentes níveis de dificuldade;
- Adicionar mais elementos visuais à interface;
- Criar diferentes modos de corrida, como multiplayer;
- Melhorar a apresentação do histórico;
- Adicionar sons ou efeitos sonoros, caso o ambiente de execução o permita.
