#include <MIDI.h>

// Definição do pino para o botão
const int buttonPin = 2; // Pino digital para o botão

// Parâmetros MIDI
const int midiChannel = 1;
const int noteC = 60;  // Nota MIDI para C (C4)

// Variáveis para o botão
int buttonState = 0;
int lastButtonState = 0;

// Instância do MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Inicializa o pino do botão como entrada com pull-up interno
  pinMode(buttonPin, INPUT_PULLUP);

  // Inicializa a comunicação MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Configura a taxa de transmissão serial
  Serial.begin(115200);
}

void loop() {
  // Lê o estado do botão
  buttonState = digitalRead(buttonPin);

  // Verifica se o botão foi pressionado
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Envia uma mensagem MIDI Note On para a nota C
    MIDI.sendNoteOn(noteC, 127, midiChannel);
    delay(100); // Pequenina pausa para evitar múltiplos envios
    // Envia uma mensagem MIDI Note Off para a nota C
    MIDI.sendNoteOff(noteC, 0, midiChannel);
  }

  // Atualiza o último estado do botão
  lastButtonState = buttonState;

  // Adicione um pequeno delay para evitar leituras excessivas
  delay(10);
}
