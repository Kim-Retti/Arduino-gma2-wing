#include <MIDI.h>

// Definição do pino para o potenciômetro
const int potPin = A0; // Pino analógico para o potenciômetro

// Parâmetros MIDI
const int midiChannel = 1;
const int noteC = 60;  // Nota MIDI para C (C4)
const int noteCSharp = 61; // Nota MIDI para C# (C#4)

// Variáveis para o potenciômetro
int potValue = 0;
int lastPotValue = 0;

// Instância do MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Inicializa o pino do potenciômetro
  pinMode(potPin, INPUT);

  // Inicializa a comunicação MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Configura a taxa de transmissão serial
  Serial.begin(115200);
}

void loop() {
  // Lê o valor do potenciômetro
  potValue = analogRead(potPin);

  // Verifica se o valor do potenciômetro mudou significativamente
  if (abs(potValue - lastPotValue) > 10) { // Ajuste o valor de 10 conforme necessário
    // Se o valor do potenciômetro aumentou (sentido horário)
    if (potValue > lastPotValue) {
      // Envia uma mensagem MIDI Note On para a nota C
      MIDI.sendNoteOn(noteC, 127, midiChannel);
      delay(100); // Pequenina pausa para evitar múltiplos envios
      // Envia uma mensagem MIDI Note Off para a nota C
      MIDI.sendNoteOff(noteC, 0, midiChannel);
    }
    // Se o valor do potenciômetro diminuiu (sentido anti-horário)
    else {
      // Envia uma mensagem MIDI Note On para a nota C#
      MIDI.sendNoteOn(noteCSharp, 127, midiChannel);
      delay(100); // Pequenina pausa para evitar múltiplos envios
      // Envia uma mensagem MIDI Note Off para a nota C#
      MIDI.sendNoteOff(noteCSharp, 0, midiChannel);
    }
    
    // Atualiza o último valor do potenciômetro
    lastPotValue = potValue;
  }

  // Adicione um pequeno delay para evitar leituras excessivas
  delay(10);
}
