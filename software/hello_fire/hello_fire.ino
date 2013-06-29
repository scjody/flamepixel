// Hello Fire: simple flamepixel test; shows an alternating checkerboard pattern.

#include <SPI.h>

// pin definitions
#define CLEARPIN 4    // master clear for 74HC595 shift registers
#define LATCHPIN 5    // latch for 74HC595 shift registers
#define OEPIN    6    // output enable for 74HC595 shift registers
#define ARMEDPIN 7    // optoisolator connected to load power
#define DATAPIN  11   // data for 74HC595 shift registers
#define CLOCKPIN 13   // clock for 74HC595 shift registers 

#define bitFlip(x,n)  bitRead(x,n) ? bitClear(x,n) : bitSet(x,n)

byte c;
byte v;
byte r1 = 0, r2 = 0;

#define PATTERN1 0b01010101
#define PATTERN2 0b10101010

// setup
void setup() {
  
  // set all output pins
  SPI.begin(); // handles DATAPIN and CLOCKPIN
  pinMode(LATCHPIN, OUTPUT);
  pinMode(OEPIN, OUTPUT);
  pinMode(CLEARPIN, OUTPUT);

  // make sure no lines go active until data is shifted out
  digitalWrite(CLEARPIN, HIGH);
  digitalWrite(OEPIN, LOW);

  // clear any lines that were left active
  digitalWrite(LATCHPIN, LOW);
  digitalWrite(OEPIN, HIGH);
  c = SPI.transfer(0);
  c = SPI.transfer(0);
  digitalWrite(LATCHPIN, HIGH);
  digitalWrite(OEPIN, LOW);
  
  // activate built-in pull-up resistor 
  digitalWrite(ARMEDPIN, HIGH);

  // start the serial communication with the xbee
  //Serial.begin(115200);
}

void set_ssr(byte b1, byte b2) {
  digitalWrite(LATCHPIN, LOW);
  digitalWrite(OEPIN, HIGH);
  c = SPI.transfer(b2);
  c = SPI.transfer(b1);
  digitalWrite(LATCHPIN, HIGH);
  digitalWrite(OEPIN, LOW);
}

void loop() {
  set_ssr(PATTERN1, PATTERN2);
  delay(500);

  set_ssr(PATTERN2, PATTERN1);
  delay(500);
}


