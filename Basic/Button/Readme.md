### Conexões

- Conecte um terminal do botão ao pino digital 2 do Arduino.
- Conecte o outro terminal do botão ao GND do Arduino.
- Utilize um resistor pull-up interno no Arduino para manter o pino em HIGH quando o botão não estiver pressionado.

### Explicação do Código

1. **Bibliotecas e Variáveis**:
   - `#include <MIDI.h>`: Inclui a biblioteca MIDI.
   - Define o pino do botão (`buttonPin`).
   - Define os parâmetros MIDI, incluindo o canal (`midiChannel`) e a nota (`noteC`).
   - Variáveis para armazenar o estado atual e anterior do botão (`buttonState` e `lastButtonState`).

2. **Setup**:
   - Configura o pino do botão como entrada com resistor pull-up interno (`pinMode(buttonPin, INPUT_PULLUP)`).
   - Inicializa a comunicação MIDI (`MIDI.begin`).
   - Inicializa a comunicação serial para depuração (`Serial.begin`).

3. **Loop**:
   - Lê o estado do botão (`digitalRead(buttonPin)`).
   - Verifica se o botão foi pressionado (transição de HIGH para LOW).
   - Se o botão foi pressionado, envia uma mensagem MIDI `NoteOn` e `NoteOff` para a nota C.
   - Atualiza o último estado do botão (`lastButtonState`).
   - Adiciona um pequeno atraso para evitar leituras excessivas (`delay(10)`).

### Conclusão

Este código permite que um botão envie um sinal MIDI `NoteOn` para a nota C (C4) quando pressionado. Quando o botão é pressionado, a nota C é enviada, e quando o botão é liberado, a nota é desligada. Certifique-se de ajustar os pinos e as notas MIDI conforme necessário para o seu projeto específico.