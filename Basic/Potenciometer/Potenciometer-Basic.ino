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
