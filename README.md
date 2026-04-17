Repositório para entrega de Checkpoint de Edge Computing, orientado por Fabio Cabrini.
============================================================
  MONITOR DE LUMINOSIDADE PARA VINHERIA
  Desenvolvido por @sia.dev
============================================================

SOBRE O PROJETO
───────────────
Este projeto implementa um sistema de monitoramento de
luminosidade para ambientes de vinheria, utilizando Arduino.

Vinhos são sensíveis à luz — a exposição excessiva degrada
taninos e altera o sabor. O sistema monitora continuamente
a intensidade luminosa do ambiente e aciona alertas visuais
e sonoros quando os limites são ultrapassados.


COMPONENTES UTILIZADOS
───────────────────────
- Arduino Uno
- Sensor LDR (Light Dependent Resistor)
- Resistor 300Ω (divisor de tensão com o LDR)
- LED verde   (sinal de ambiente seguro)
- LED amarelo (sinal de alerta)
- LED vermelho (sinal de perigo)
- 3x Resistores 300Ω (um para cada LED)
- Buzzer passivo
- Display LCD 16x2


LIGAÇÕES (PINAGEM)
───────────────────
LDR:
  Terminal 1  → 5V
  Terminal 2  → Pino A0  +  resistor 10kΩ → GND

LEDs:
  LED verde    → pino 9  → resistor 300Ω → GND
  LED amarelo  → pino 8  → resistor 300Ω → GND
  LED vermelho → pino 7  → resistor 300Ω → GND

Buzzer:
  Pino +  → pino 6
  Pino -  → GND

LCD 16x2 (modo 4 bits):
  VSS → GND
  VDD → 5V
  V0  → GND
  RS  → pino 12
  RW  → GND
  E   → pino 11
  D4  → pino 5
  D5  → pino 4
  D6  → pino 3
  D7  → pino 2
  A (backlight) → 5V via resistor 300Ω
  K (backlight) → GND


COMO FUNCIONA
──────────────
O LDR é ligado em divisor de tensão com um resistor fixo
de 300Ω. Quanto mais luz incide no LDR, menor é sua
resistência, e maior é a tensão no pino A0.

O ADC (Conversor Analógico-Digital) do Arduino converte
essa tensão em um valor inteiro de 0 a 1023.

A função map() converte esse valor bruto para uma escala
de 0 a 100%, facilitando a leitura e definição de limites.

  map(ldrStatus, 2, 381, 0, 100)

Os valores 2 e 381 foram calibrados para o ambiente
específico da vinheria — ajuste conforme necessário.


FAIXAS DE LUMINOSIDADE
───────────────────────
  0%  a 19%  → SEGURO   — LED verde aceso
  20% a 59%  → ALERTA   — LED amarelo pisca + buzzer (3s)
  60% a 100% → PERIGO   — LED vermelho pisca + buzzer contínuo


COMPORTAMENTO DO SISTEMA
─────────────────────────
Inicialização:
  Ao ligar, o LCD exibe a mensagem de boas-vindas com o
  logo "@sia.dev", seguida de "Iniciando..." e então
  a tela principal do monitor.

Tela principal:
  Linha 1: "Vinhos @sia.dev"
  Linha 2: status (seguro/alerta/perigo) + porcentagem

Estado SEGURO (luminosidade < 20%):
  - LED verde aceso
  - LCD exibe "seguro" + porcentagem
  - Nenhum alerta sonoro

Estado ALERTA (20% ≤ luminosidade < 60%):
  - LED amarelo pisca 5 vezes (3 segundos)
  - Buzzer soa durante as piscadas
  - LCD exibe "alerta" + porcentagem
  - Caso a luminosidade permaneça em alerta,
    o ciclo de piscadas se repete

Estado PERIGO (luminosidade ≥ 60%):
  - LED vermelho pisca continuamente
  - Buzzer soa continuamente
  - LCD exibe "perigo" + porcentagem


LÓGICA DE ESTADOS
──────────────────
O sistema utiliza a variável "estadoAnterior" para evitar
que as funções de alerta sejam chamadas repetidamente.
As funções seguro(), alerta() e perigo() são chamadas
apenas UMA VEZ no momento em que o estado muda — não a
cada ciclo do loop().

Isso permite que o LED amarelo pisce um número definido
de vezes ao entrar em alerta, sem repetição indesejada.

A variável "luminosidadeAnterior" evita flickering no LCD
— a porcentagem só é redesenhada quando o valor muda.


CALIBRAÇÃO
───────────
Para calibrar o LDR para o seu ambiente:
  1. Abra o Serial Monitor (9600 baud)
  2. Observe os valores brutos do analogRead()
  3. Anote o valor em ambiente escuro (mínimo)
     e em luz máxima esperada (máximo)
  4. Substitua os valores na função map():
     map(ldrStatus, MINIMO, MAXIMO, 0, 100)


SERIAL MONITOR
───────────────
Com o Serial Monitor aberto a 9600 baud, o sistema
exibe continuamente o valor bruto do ADC (0–1023),
útil para calibração e diagnóstico.


============================================================
  Projeto desenvolvido por @sia.dev
============================================================
