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
 
 

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 5;       // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int buttonPin1 = 2;
int buttonPin2 = 3;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT);
  
  DDRB = B11111100;
  DDRD = DDRD | B11000000;
}

void writeByte(int in) {
  PORTB = in;
  PORTD = in;
}

void writeByteGood(int x) {
  int pin;
  
  for (pin=13; pin>=6; pin--) {
    digitalWrite(pin, x&1);
    x >>= 1;
  }
}

int counter = 0;

void loop() {
  counter += 8;
  if (counter > 255) counter = 0;

  // write to the digital pins
  writeByte(counter);
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  
  int button1 = digitalRead(buttonPin1);
  int button2 = digitalRead(buttonPin2);
  
  // if either button is pressed, turn on the LED
  if (button1 ^ button2)
    digitalWrite(ledPin, HIGH);  
  else
    digitalWrite(ledPin, LOW);
}
