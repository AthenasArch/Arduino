#include <Arduino.h>

// Defina os pinos para os segmentos dos displays
int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};

// Defina os pinos para os transistores
int transistorPins[] = {9, 10, 11, 12};

// Defina o pino do potenciômetro
int potPin = A0;

// Armazene os códigos binários para cada número para o display de 7 segmentos
byte number[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

uint16_t getCntDisplay(void);

void rundDisplay(void);


void setup() {
    // Defina os pinos de segmentos e transistores como saída
    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins[i], OUTPUT);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(transistorPins[i], OUTPUT);
        digitalWrite(transistorPins[i], HIGH); // Inicialmente desligado (ativo baixo)
    }

    // for(int i = 0; i < 7; i++){
    //     digitalWrite(segmentPins[i], 1);
    //     delay(500);
    //     digitalWrite(segmentPins[i], 0);
    //     delay(500);
    // }
}


void loop() {
    
    uint16_t delayTime = map(analogRead(potPin), 0, 1023, 0, 500); // Leia o valor do potenciômetro para ajustar o atraso
    uint16_t counter = getCntDisplay(); // Obtém o valor atual do contador

    if(delayTime < 5){
        delayTime = 3;
    }


    // Dividir o contador em dígitos individuais
    int digits[4];
    digits[0] = (counter / 1000) % 10; // Dígito mais significativo
    digits[1] = (counter / 100) % 10;
    digits[2] = (counter / 10) % 10;
    digits[3] = counter % 10; // Dígito menos significativo

    for (int digit = 0; digit < 4; digit++) { // Itere sobre cada dígito/display

        for (uint8_t segment = 0; segment < 7; segment++) { // Itere sobre cada segmento
            digitalWrite(segmentPins[segment], bitRead(number[digits[digit]], segment)); // Acenda o segmento correto
        }
        
        digitalWrite(transistorPins[digit], LOW); // Ative o display atual (ativo baixo)
        delay(delayTime); // Aguarde o tempo definido
        digitalWrite(transistorPins[digit], HIGH); // Desative o display atual (ativo baixo)
    }
}





// void loop() {
//     uint16_t delayTime = map(analogRead(potPin), 0, 1023, 1, 1000); // Leia o valor do potenciômetro para ajustar o atraso

//     for (int digit = 0; digit < 4; digit++) { // Itere sobre cada dígito/display
        
//         digitalWrite(transistorPins[digit], LOW); // Ative o display atual (ativo baixo)
        
//         for (uint8_t segment = 0; segment < 7; segment++) { // Itere sobre cada segmento
//             digitalWrite(segmentPins[segment], bitRead(number[2], segment)); // Acenda o segmento correto
//         }
        
//         delay(delayTime); // Aguarde o tempo definido
//         digitalWrite(transistorPins[digit], HIGH); // Desative o display atual (ativo baixo)
//     }
// }

uint16_t getCntDisplay(void){

    static unsigned long cnt = 0;
    const uint16_t MAX_CNT = 9999;
    static unsigned long timerCnt = 0;
    const uint16_t TIME_CNT = 1000;

    if(millis() - timerCnt > TIME_CNT){
        timerCnt = millis();
    
        if(cnt >= MAX_CNT ){
            cnt = 0;
        } else {
            cnt++;
        }
    }
    return cnt;
}