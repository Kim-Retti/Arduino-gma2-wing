#include "MIDIUSB.h"

// Define os pinos dos botões
const int BUTTON_PIN_1 = 2; // Botão principal (não utilizado atualmente)
const int BUTTON_PIN_ALT = 0; // Botão de alternância
const int BUTTON_PIN_EXEC = 1; // Botão exec_101

// Define as notas MIDI
const byte BUTTON_NOTE_1 = 62;
const byte BUTTON_NOTE_EXEC_BASE = 1;
const byte BUTTON_NOTE_EXEC_ALT_1 = 2;
const byte BUTTON_NOTE_EXEC_ALT_2 = 3;
const byte BUTTON_NOTE_ALT_PAGE = 51;

// Estados atuais e anteriores dos botões
int buttonCState1 = HIGH;
int buttonPState1 = HIGH;

int buttonCStateAlt = HIGH;
int buttonPStateAlt = HIGH;
int altPageState = 0; // Estado do botão de alternância

int buttonCStateExec = HIGH;
int buttonPStateExec = HIGH;

void setup() {
  // Inicializa a comunicação serial para depuração
  Serial.begin(115200);

  // Configura os pinos dos botões como entradas com resistores de pull-up internos
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_ALT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_EXEC, INPUT_PULLUP);
}

void loop() {
  // Lê o estado do botão de alternância
  buttonCStateAlt = digitalRead(BUTTON_PIN_ALT);
  if (buttonCStateAlt != buttonPStateAlt) {
    if (buttonCStateAlt == LOW) {
      // Alterna o estado do botão de alternância
      altPageState++;
      if (altPageState > 3) {
        altPageState = 0;
      }
    }
    buttonPStateAlt = buttonCStateAlt;
  }

  // Lê o estado do botão exec_101
  buttonCStateExec = digitalRead(BUTTON_PIN_EXEC);
  if (buttonCStateExec != buttonPStateExec) {
    byte noteToSend;
    if (altPageState == 0) {
      noteToSend = BUTTON_NOTE_EXEC_BASE;
    } else if (altPageState == 1) {
      noteToSend = BUTTON_NOTE_EXEC_ALT_1;
    } else if (altPageState == 2) {
      noteToSend = BUTTON_NOTE_EXEC_ALT_2;
    } else {
      // No estado 3, o botão exec_101 não faz nada
      noteToSend = 0;
    }

    if (noteToSend != 0) {
      if (buttonCStateExec == LOW) {
        // Envia a mensagem Note On para a nota correspondente
        noteOn(0, noteToSend, 127);
      } else {
        // Envia a mensagem Note Off para a nota correspondente
        noteOff(0, noteToSend, 0);
      }
    }
    buttonPStateExec = buttonCStateExec;
    MidiUSB.flush();
  }

  // No estado 3, o botão alt_page envia a mensagem Note On para a nota 51 e reseta o estado
  if (altPageState == 3) {
    if (buttonCStateAlt == LOW) {
      // Envia a mensagem Note On para a nota 51
      noteOn(0, BUTTON_NOTE_ALT_PAGE, 127);
      delay(100); // Delay para garantir que a nota seja registrada
      noteOff(0, BUTTON_NOTE_ALT_PAGE, 0);
      MidiUSB.flush();
      altPageState = 0; // Reseta o estado para 0
    }
  }

  // Pequeno atraso para debouncing
  delay(10);
}

// Função para enviar uma mensagem Note On
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

// Função para enviar uma mensagem Note Off
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
