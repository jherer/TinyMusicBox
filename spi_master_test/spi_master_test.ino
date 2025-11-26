
// include the SPI library:
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int CS = 10;
#define SPI_RST 9

void setup() {
  pinMode(SPI_RST, OUTPUT);
  pinMode(SPI_RST, LOW);

  Serial.begin(9600);
  // set the slaveSelectPin as an output:
  while (!Serial);
  //establishContact();
  // initialize SPI:pinMode(MOSI, INPUT);
  pinMode(MISO, INPUT);
  pinMode(SCK, INPUT);
  pinMode(CS, INPUT);
  delay(500); // give Micro time to boot & enumerate

  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  digitalWrite(SPI_RST, HIGH);
  SPI.begin();
  
}


void send(uint8_t cmd, uint8_t data) {
  digitalWrite(CS, LOW); // Select the slave
  SPI.beginTransaction(SPISettings(125000, MSBFIRST, SPI_MODE0));
  
  byte cmdResponse = SPI.transfer(cmd); // Send and receive simultaneously
  delay(25);
  byte dataResponse = SPI.transfer(data); // Send and receive simultaneously
  delay(25);
  digitalWrite(CS, HIGH); // Deselect the slave
  SPI.endTransaction();

  Serial.print("Master sent: ");
  Serial.print(cmd, HEX);
  Serial.print(data, HEX);
  Serial.print(", Slave responded: ");
  Serial.print(cmdResponse, HEX);
  Serial.println(dataResponse, HEX);
}


void loop() {
  send(0x55, 0xaa);
  delay(1000); // Wait for a second
  send(0x55, 0xcc);
  delay(1000); // Wait for a second
}


/*
void loop() {
  int i = 0;
  uint16_t hexCode = 0;

  while (true) {
    while (!Serial.available());
    uint8_t readByte = Serial.read();

    if (isHexadecimalDigit(readByte) && i < 4) {
      hexCode = (hexCode << 4) + asciiToHex(readByte);
      i++;
    } else {
      i = 0;
      Serial.print("Invalid entry ");
      clearBuffer();
    }

    if (i == 4) {
      i = 0;
      uint8_t cmd = (hexCode & 0xFF00) >> 8; // get top byte
      uint8_t data = hexCode & 0x00FF; // get bottom byte
      Serial.print("cmd: 0x");
      Serial.print(cmd, HEX);
      Serial.print(" data: 0x");
      Serial.println(data, HEX);
      writeSPI(cmd, data);
      clearBuffer();
    }
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');  // send a capital A
    delay(300);
  }
}

void writeSPI(int address, int value) {
  // take the SS pin low to select the chip:
  SPI.beginTransaction(SPISettings(20000, MSBFIRST, SPI_MODE0));
  digitalWrite(slaveSelectPin, LOW);
  delay(10);
  // send in the address and value via SPI:
  uint8_t b1 = SPI.transfer(address);
  uint8_t b0 = SPI.transfer(value);
  delay(10);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
  delay(10);
  SPI.endTransaction();
  Serial.print(b1, HEX);
  Serial.print("  ");
  Serial.println(b0, HEX);
}


void clearBuffer() {
  while (Serial.available()) {
    Serial.read();
  }
}


uint8_t asciiToHex(uint8_t receivedChar) {
  uint8_t hexValue = 0;
  if (isHexadecimalDigit(receivedChar)) { // Check if it's a valid hex digit
    if (receivedChar >= '0' && receivedChar <= '9') {
      hexValue = receivedChar - '0';
    } else if (receivedChar >= 'A' && receivedChar <= 'F') {
      hexValue = receivedChar - 'A' + 10;
    } else if (receivedChar >= 'a' && receivedChar <= 'f') {
      hexValue = receivedChar - 'a' + 10;
    }  
  }
  return hexValue;
}*/