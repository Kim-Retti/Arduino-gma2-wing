### Conexões

- Conecte o pino A do encoder ao pino 2 do Arduino.
- Conecte o pino B do encoder ao pino 3 do Arduino.
- Conecte o pino comum (GND) do encoder ao GND do Arduino.

### Explicação do Código

1. **Bibliotecas e Variáveis**:
   - `#include <MIDI.h>`: Inclui a biblioteca MIDI.
   - Definimos os pinos do encoder (`encoderPinA` e `encoderPinB`).
   - Definimos os parâmetros MIDI, incluindo o canal (`midiChannel`) e as notas (`noteC` e `noteCSharp`).
   - Variáveis do encoder (`encoderValue` e `lastEncoded`).

2. **Setup**:
   - Configura os pinos do encoder como entradas com resistores de pull-up internos.
   - Configura interrupções para detectar mudanças nos pinos do encoder (`attachInterrupt`).
   - Inicializa a comunicação MIDI (`MIDI.begin`).
   - Inicializa a comunicação serial para depuração (`Serial.begin`).

3. **Loop**:
   - Verifica se o valor do encoder mudou.
   - Se o valor aumentou (giro no sentido horário), envia uma mensagem MIDI `NoteOn` e `NoteOff` para a nota C.
   - Se o valor diminuiu (giro no sentido anti-horário), envia uma mensagem MIDI `NoteOn` e `NoteOff` para a nota C#.
   - Atualiza o último valor do encoder.

4. **Função de Interrupção `updateEncoder`**:
   - Lê os valores dos pinos do encoder.
   - Calcula a direção do giro do encoder.
   - Atualiza o valor do encoder (`encoderValue`).

### Conclusão

Este código permite que um encoder rotativo envie sinais MIDI `NoteOn` para duas notas diferentes, dependendo da direção da rotação. Isso pode ser útil em vários projetos musicais e de controle. Certifique-se de ajustar os pinos e as notas MIDI conforme necessário para o seu projeto específico.