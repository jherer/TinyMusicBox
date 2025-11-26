#include "mySPI.hpp"
#include <avr/interrupt.h>


#define NUM_BYTES 2

volatile uint8_t dataBuffer[NUM_BYTES] = {0};
volatile uint8_t index = 0;
volatile bool buffOvf = false;

#define SS_PIN   PB3
#define MISO_PIN PB1
#define MOSI_PIN PB0
#define SCK_PIN  PB2

#define CHECK_BIT(var,pos) (((var) & (1<<(pos))) > 0)

void initSPI() {
  DDRB |= (1 << MISO_PIN);    // MISO as output
  DDRB &= ~((1 << PB0) | (1 << PB2));  // MOSI, SCK inputs
  DDRB &= ~(1 << PB3); // SS input
  PORTB |= (1 << PB3); // SS PULLUP
      
  USICR =
    (1 << USIWM0) |  // 3-wire mode
    (1 << USICS1) |  // Clock from external pin (USCK)
    (0 << USICS0);   // No software clock
  
  // Clear flags
  USISR = (1 << USIOIF);
  USICR |= (1 << USIOIE);  // enable USI overflow interrupt
  USIDR = 0xa5; // Optional: preload outgoing byte

}

void updateSPI() {
  // Check if slave is selected
  if (!(PINB & (1 << SS_PIN))) {
    // SS LOW → enable MISO output
    DDRB |= (1 << MISO_PIN);
  } else {
    // SS HIGH → tri-state MISO (critical!!)
    DDRB &= ~(1 << MISO_PIN);
    USISR = (1 << USIOIF);
    index = 0;
  }
}

uint8_t getSPIIn(uint8_t i) {
  if (i >= NUM_BYTES) {
    i = NUM_BYTES - 1;
  }
  return dataBuffer[i];
}

void clearSPIBuffer() {
  buffOvf = false;
}

bool isSPIReady() {
  return buffOvf;
}


// run interrupt whenever USI overflows (full 8 bits)
ISR(USI_OVF_vect) {
  int dataIn = USIDR;
  dataBuffer[index] = dataIn;
  USIDR = dataIn + 1;
  USISR = (1 << USIOIF);
  
  index++;
  if (index >= NUM_BYTES) {
    index = 0;
    buffOvf = true;
  }
}
