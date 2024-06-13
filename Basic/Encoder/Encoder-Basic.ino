#include <MIDI.h>

// Definições de pinos para o encoder
const int encoderPinA = 2; // Pino A do encoder
const int encoderPinB = 3; // Pino B do encoder

// Parâmetros MIDI
const int midiChannel = 1;
const int noteC = 60;  // Nota MIDI para C (C4)
const int noteCSharp = 61; // Nota MIDI para C# (C#4)

// Variáveis do encoder
volatile int encoderValue = 0;
int lastEncoded = 0;

// Instância do MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Inicializa os pinos do encoder
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  
  // Inicializa interrupções para o encoder
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

  // Inicializa a comunicação MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Configura a taxa de transmissão serial
  Serial.begin(115200);
}

void loop() {
  static int lastEncoderValue = 0;
  
  // Verifica se o valor do encoder mudou
  if (encoderValue != lastEncoderValue) {
    // Se o encoder foi girado para a direita
    if (encoderValue > lastEncoderValue) {
      // Envia uma mensagem MIDI Note On para a nota C
      MIDI.sendNoteOn(noteC, 127, midiChannel);
      delay(100); // Pequenina pausa para evitar múltiplos envios
      // Envia uma mensagem MIDI Note Off para a nota C
      MIDI.sendNoteOff(noteC, 0, midiChannel);
    }
    // Se o encoder foi girado para a esquerda
    else {
      // Envia uma mensagem MIDI Note On para a nota C#
      MIDI.sendNoteOn(noteCSharp, 127, midiChannel);
      delay(100); // Pequenina pausa para evitar múltiplos envios
      // Envia uma mensagem MIDI Note Off para a nota C#
      MIDI.sendNoteOff(noteCSharp, 0, midiChannel);
    }
    
    // Atualiza o último valor do encoder
    lastEncoderValue = encoderValue;
  }
}

void updateEncoder() {
  // Lê os valores dos pinos do encoder
  int MSB = digitalRead(encoderPinA); // Pino A do encoder
  int LSB = digitalRead(encoderPinB); // Pino B do encoder
  
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;
  
  // Determina a direção do giro
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue--;
  
  // Atualiza o último valor codificado
  lastEncoded = encoded;
}
