Claro! Aqui está a explicação detalhada do código que você pode usar para o GitHub:

---

# MIDI Potentiometer Controller

Este projeto utiliza um potenciômetro para controlar a velocidade de uma nota MIDI enviada via USB. A biblioteca `MIDIUSB.h` é usada para enviar mensagens MIDI para um dispositivo host, como um computador. Quando o valor do potenciômetro é alterado, a velocidade (intensidade) da nota MIDI enviada é ajustada. Se o potenciômetro estiver em 0, uma mensagem `NoteOff` será enviada para parar a nota.

## Componentes

- Arduino (compatível com MIDI via USB, como o Arduino Leonardo ou o Arduino Micro)
- Potenciômetro
- Fios de conexão

## Conexões

- Conecte o pino central do potenciômetro ao pino analógico A0 do Arduino.
- Conecte um dos pinos externos do potenciômetro ao GND.
- Conecte o outro pino externo do potenciômetro ao 5V.

## Código

```cpp
#include <MIDIUSB.h>

// Definição do pino para o potenciômetro
const int potPin = A0; // Pino analógico para o potenciômetro

// Parâmetros MIDI
const int midiChannel = 1;
const int noteC = 60;  // Nota MIDI para C (C4)

// Variáveis para o potenciômetro
int potValue = 0;
int lastPotValue = 0;
int velocity = 0;

void setup() {
  // Inicializa o pino do potenciômetro
  pinMode(potPin, INPUT);

  // Configura a taxa de transmissão serial para depuração
  Serial.begin(115200);
}

void loop() {
  // Lê o valor do potenciômetro
  potValue = analogRead(potPin);

  // Verifica se o valor do potenciômetro mudou significativamente
  if (abs(potValue - lastPotValue) > 10) { // Ajuste o valor de 10 conforme necessário
    // Mapeia o valor do potenciômetro (0-1023) para o intervalo de velocidade MIDI (0-127)
    velocity = map(potValue, 0, 1023, 0, 127);
    
    // Se o valor do potenciômetro for maior que 0, envia uma mensagem Note On
    if (potValue > 0) {
      noteOn(midiChannel, noteC, velocity);
    } else {
      // Se o valor do potenciômetro for 0, envia uma mensagem Note Off
      noteOff(midiChannel, noteC, 0);
    }
    
    // Atualiza o último valor do potenciômetro
    lastPotValue = potValue;
  }

  // Adicione um pequeno delay para evitar leituras excessivas
  delay(10);
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}
```

## Explicação do Código

### Inclusão da Biblioteca

```cpp
#include <MIDIUSB.h>
```

Incluímos a biblioteca `MIDIUSB.h` para lidar com mensagens MIDI via USB.

### Definição de Pinos e Parâmetros MIDI

```cpp
const int potPin = A0; // Pino analógico para o potenciômetro
const int midiChannel = 1; // Canal MIDI
const int noteC = 60;  // Nota MIDI para C (C4)
```

Definimos o pino do potenciômetro e os parâmetros MIDI, como o canal MIDI e a nota C (C4).

### Variáveis para o Potenciômetro

```cpp
int potValue = 0;
int lastPotValue = 0;
int velocity = 0;
```

Declaramos variáveis para armazenar o valor atual e anterior do potenciômetro, além da velocidade (intensidade) da nota MIDI.

### Função `setup()`

```cpp
void setup() {
  pinMode(potPin, INPUT);
  Serial.begin(115200);
}
```

Inicializamos o pino do potenciômetro como entrada e configuramos a taxa de transmissão serial para depuração.

### Função `loop()`

```cpp
void loop() {
  potValue = analogRead(potPin);

  if (abs(potValue - lastPotValue) > 10) {
    velocity = map(potValue, 0, 1023, 0, 127);
    
    if (potValue > 0) {
      noteOn(midiChannel, noteC, velocity);
    } else {
      noteOff(midiChannel, noteC, 0);
    }
    
    lastPotValue = potValue;
  }

  delay(10);
}
```

No loop principal, lemos o valor do potenciômetro e verificamos se ele mudou significativamente. Se mudou, mapeamos o valor do potenciômetro para o intervalo de velocidades MIDI (0-127). Se o valor for maior que 0, enviamos uma mensagem `NoteOn` com a velocidade correspondente. Se o valor for 0, enviamos uma mensagem `NoteOff`.

### Funções `noteOn` e `noteOff`

```cpp
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}
```

Essas funções constroem pacotes MIDI para mensagens `NoteOn` e `NoteOff` e os enviam via USB usando a função `MidiUSB.sendMIDI()`. A função `MidiUSB.flush()` é chamada para garantir que as mensagens sejam transmitidas imediatamente.

---

Este código permite controlar a intensidade de uma nota MIDI usando um potenciômetro, com mensagens MIDI sendo enviadas via USB para um dispositivo host.