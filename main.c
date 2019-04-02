#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main() {
  int i = 0;
  Init();
  while (1){
    // From example, OCR0A here is changing constantly from 0 - 100 - 0
    for(i=0;i<=255;i++){
      OCR0A = i;
      _delay_ms(10);
    }
    for(;i>=0;i--){
      OCR0A = i;
      _delay_ms(10);
    }
  }
  return 1;
}

void Init() {
  // Enable global interrupts
  sei();
}