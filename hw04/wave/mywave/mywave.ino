/*
  Use this sketch to test the SoftSysSynth.
  
  Remove the speaker and run a resistor from the emitter of the transistor to ground
  (effectively bypassing the decoupling capacitor and the speaker).
  
  Then run a wire from the emitter to A0.
  
  When you run this sketch, open the serial monitor.  The input is on the left.
  The value at A0 is on the right.  With the 0.7 V offset, the value at A0 should
  equal the input value minus ~36.
 
  Author: Allen Downey 
  Edited by: Evan Dorsky
 
  Based on http://arduino.cc/en/Tutorial/AnalogInput
  Created by David Cuartielles, modified by Tom Igoe.

  License: Public Domain
 
 */
 
 #include "Waveforms.h"
 
int buttonInterrupt = 1;
int buttonPin = 5;
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(buttonInterrupt, buttonPress, FALLING);
  
  DDRB = B00111111;
  DDRD = DDRD | B11000000;

  cli();//stop interrupts

  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 240;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  sei();//allow interrupts
}

int wave0 = 0;

void buttonPress() {
  wave0 = (wave0+1) % 4;
}

int counter = 0, i = 0;

ISR(TIMER0_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
  i = (i+1) % maxSamplesNum;
  writeByte(waveformsTable[wave0][i]);
}

void writeByte(int in) {
  PORTB = (in >> 2);
  PORTD = (in << 6);
}

void loop() {
}