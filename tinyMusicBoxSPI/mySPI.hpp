

void initSPI();
/*
void setSPIOut(unsigned char newDataOut);
bool getSPIReady();
unsigned char getSPIIn();
unsigned char getSPINumBytes();
*/
void updateSPI();
unsigned char getSPIIn(unsigned char i);
//void setSPIOut(unsigned char newDataOut);
bool isSPIReady();
void clearSPIBuffer();



/*#include "mySPI.hpp"
#include <avr/interrupt.h>


volatile buffer[2];
volatile index = 0;

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


void setSPIOut(uint8_t newDataOut) {
  dataOut = newDataOut;
}

bool getSPIReady() {
  return ready;
}

uint8_t getSPIIn() {
  ready = false;
  return dataIn;
}

uint8_t getSPINumBytes() {
  return numBytes;
}

void updateSPI() {
  // Check if slave is selected
  if (!(PINB & (1 << SS_PIN))) {
    // SS LOW → enable MISO output
    DDRB |= (1 << MISO_PIN);
  } else {
    // SS HIGH → tri-state MISO (critical!!)
    DDRB &= ~(1 << MISO_PIN);
    numBytes = 0;
  }
}

// run interrupt whenever USI overflows (full 8 bits)
ISR(USI_OVF_vect) {


  dataIn = USIDR;
  USIDR = dataOut;
  USISR = (1 << USIOIF);
  numBytes++;
  ready = true;
}
*/