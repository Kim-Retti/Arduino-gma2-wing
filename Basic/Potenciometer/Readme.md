### Conexões

- Conecte a extremidade esquerda do potenciômetro ao GND do Arduino.
- Conecte a extremidade direita do potenciômetro ao 5V do Arduino.
- Conecte o pino central do potenciômetro ao pino analógico A0 do Arduino.

### Explicação do Código

1. **Bibliotecas e Variáveis**:
   - `#include <MIDI.h>`: Inclui a biblioteca MIDI.
   - Define o pino do potenciômetro (`potPin`).
   - Define os parâmetros MIDI, incluindo o canal (`midiChannel`) e as notas (`noteC` e `noteCSharp`).
   - Variáveis para armazenar o valor atual e anterior do potenciômetro (`potValue` e `lastPotValue`).

2. **Setup**:
   - Configura o pino do potenciômetro como entrada (`pinMode(potPin, INPUT)`).
   - Inicializa a comunicação MIDI (`MIDI.begin`).
   - Inicializa a comunicação serial para depuração (`Serial.begin`).

3. **Loop**:
   - Lê o valor do potenciômetro (`analogRead(potPin)`).
   - Verifica se o valor do potenciômetro mudou significativamente (usando uma diferença mínima de 10).
   - Se o valor aumentou (girado no sentido horário), envia uma mensagem MIDI `NoteOn` e `NoteOff` para a nota C.
   - Se o valor diminuiu (girado no sentido anti-horário), envia uma mensagem MIDI `NoteOn` e `NoteOff` para a nota C#.
   - Atualiza o último valor do potenciômetro (`lastPotValue`).
   - Adiciona um pequeno atraso para evitar leituras excessivas (`delay(10)`).

### Conclusão

Este código permite que um potenciômetro envie sinais MIDI `NoteOn` para duas notas diferentes, dependendo do aumento ou diminuição do valor lido pelo potenciômetro. Quando o potenciômetro é girado no sentido horário, a nota C (C4) é enviada. Quando é girado no sentido anti-horário, a nota C# (C#4) é enviada. Certifique-se de ajustar os pinos e as notas MIDI conforme necessário para o seu projeto específico.