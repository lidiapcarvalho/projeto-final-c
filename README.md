# 🏎️ Corrida - Jogo de Corrida em C

## 📖 Descrição

Este projeto consiste no desenvolvimento de um jogo de corrida em modo texto, programado em linguagem C e utilizando a biblioteca `ncurses` para a interface no terminal.

O jogador controla um carro numa pista representada através de uma matriz, devendo completar três voltas no menor tempo possível. O jogo inclui um sistema de controlo do tempo, deteção de voltas através de checkpoints, registo dos tempos das corridas e um histórico persistente.

## 🎯 Objetivo do jogo

O objetivo é completar três voltas ao circuito no menor tempo possível.

Para que uma volta seja validada, o jogador deve passar pelos checkpoints definiddos ao longo da pista antes de atravessar novamente a linha de chegada.

No final das trâs voltas, o tempo total da corrida é apresentado e guardado no histórico.

## 🎮 Como jogar

> Ao iniciar o programa, é apresentado um menu principal onde o jogador pode escolher entre iniciar uma corrida, consultar o histórico de corridas ou sair do programa.

Durante a corrida, o jogador controla o carro através das teclas direcionais.

### Controlos

| **Tecla** | **Ação**                      |
| --------- | ----------------------------- |
| `↑`       | Mover o carro para cima       |
| `↓`       | Mover o carro para baixo      |
| `→`       | Mover o carro para a esquerda |
| `←`       | Mover o carro para a direito  |
| `ESC`     | Sair / Interromper a corrida  |

### Regras

- A corrida é ccomposta por 3 voltas.
- O carro só pode deslocar-se pelas posições consideradas válidas da pista.
- Os checkpoints têm de ser percorridos pela ordem definida.
- Uma volta só é contabilizada quandos os checkpoints necessários foram completados e o carro atravessa a linha da meta.
- O tempo dda corrida é medido desde o início até à conclusão das três voltas.
- No final da corrida, o tempo é apresentado e guardado no histórico.

## 🗺️ A pista

A psita é representada através de uma matriz de caracteres.

Cada posição da matriz corresponde a uma posição possível do circuito. O carácter `#` representa a estrada da pista, enquanto `=` representa a linha da meta/chegada.

O circuito é desenhado no terminal através da biblioteca `ncurses`.

### Sistema de voltas e checkpoints

Para evitar que uma volta seja contabilizada apenas por atravessar a linha da meta, foram definidos checkpoints intermédios.

Os checkpoints funcionam como pontos de validação da volta: o jogador deve passar pelos checkpoints na ordem correta antes de atravessar novamente a linha da meta.

Este sistema foi inspirado no funcionamento dos setores de uma pista de Fórmula 1, onde a passagem por diferentes pontos do circuito permite acompanhar e validar a posição do carro.

## ⏱️ Sistema de tempo

O tempo de cada corrida é medido desde o início da corrida até à conclusão das três voltas.

Para medir o tempo foi utilizada a função `clock_gettime()` com o relógio monotónico `CLOCK_MONOTONIC`. Este relógio é adequado para medir intervalos de tempo, uma vez que não é afetado por alterações à data ou à hora do sistema durante a ezecução do programa.

A função `get_time_ms()` obtém o tempo através de duas componentes:
- `tv_sec` - número de segundos;
- `tv_nsec` - número de nanossegundos.

Estes valores são convertidos para milissegundos, permitindo calcular a duração da corrida com precisão.

O tempo inicial é registado no início da corrida e, quando as três voltas são concluídas, é calculada a diferença entre o tempo final e o tempo inicial.

O resultado é posteriormente convertido de milissegundos para segundos e apresentado com duas casas decimais.

### Controlo da velocidade

A velocidade do carro também influencia o intervalo entre movimentos. O atraso utilziado entre movimentos é ajustado através da função `get_speed_delay()`, permitindo que diferentes velocidades correspondam a diferentes tempos de espera.

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

Os tempos são guardados em milissegundos e apresentados no jogo em segundos, com duas casas deciamais.

O histórico é carregado a partir do ficheiro quando o programa é executado, permitindo manter os resultados entre diferentes utilizações do jogo.

Para a apresentação dos resultado foi implementada uma função recursiva, `draw_history_recursive()`, que percorre os registos do histórico e apresenta cada corrida no ecrã.

O número de corridas mantidas em memória está atualmente limitado através da constante `MAX_RACES`, definida com o valor 10.

### Apresentação - temporário

Cada registo é apresentado com o número da corrida, a data, a hora e o respetivo tempo:

Corrida 1 | 28/08/2026 | 18:59 | 32,00 s
Corrida 2 | 28/08/2026 | 20:17 | 26,85 s

O sistema de histórico permite acompanhar a evolução dos tempos obtidos ao longo das corridas.

## 🎨 Interface

## 📁 Estrutura do projeto

O projeto está organziado em vários ficheiros, de forma a separar as diferentes responsabilidades do jogo.
| **Ficheiro**      | **Responsabilidade**                                                                                                                 |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| `main.c`          | Função principal do programa e gestão do fluxo geral do jogo e do menu.                                                              |
| `game.c`          | Gestão da lógica principal da corrida, incluindo voltas, checkpoints, início e fim da corrida e apresentação dos resultados.         |
| `game.h`          | Declaração das funções e variáveis píblicas relacionadas com a lógica do jogo.                                                       |
| `track.h`         | Definição e desenho da pista.                                                                                                        |
| `track.h`         | Declarações relacionadas com a pista.                                                                                                |
| `car.c`           | Gestão da posição e do movimento do carro.                                                                                           |
| `car.h`           | Declarações relacionadas com o carro.                                                                                                |
| `timer.c`         | Medição do tempo da corrida e cálculo dos atrasos associados à velocidade.                                                           |
| `timer.h`         | Declarações relacionadas com o sistema de tempo.                                                                                     |
| `menu.c`          | Implementação e apresentação do menu principal.                                                                                      |
| `menu.h`          | Declarações relacionadas com o menu.                                                                                                 |
| `history.c`       | Gestão de histórico de corridas, incluido gravação, carregamento e apresentação dos resultados.                                      |
| `history.h`       | Declarações relacionadas com o histórico.                                                                                            |   
| `historico.txt`   | Ficheiro utilizado para guardar os resultados das corridas entre diferentes execuções do programa.                                   |
| `Makefile`        | Automatização da compilação e ligação dos diferentes ficheiros do projeto.                                                           |
| `READNE.md`       | Documentação do projeto, incluindo o funcionamento, estrutura, utilização e referências.                                             |
| `LOG.md`          | Registo do desenvolvimento do projeto, das funcionalidades implementadas, dificuldades e alterações realizadas ao longo das sessões. |
| `apontamentos.md` | Registo de notas técnicas, explicações e aprendizagens realizadas durante o desenvolvimento do projeto.                              |


## 🧠 Conceitos de programação utilizados

## 🛠️ Tecnologias utilizadas

## ▶️ Compilação e execução

## 📚 Bibliografia e referências

## 🚧 Melhorias futuras
