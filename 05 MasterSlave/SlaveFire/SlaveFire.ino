/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */
#include <Wire.h>
#include <IRremote.h>
// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
IRsend irsend;
unsigned long lastfire=0;
int firerate=500;
int shots = 0;

void setup() {
    Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
   Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  lastfire = millis();
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);


}

void receiveEvent(int howMany) {
  while ( Wire.available()) { // loop through all but the last
    char x  = Wire.read(); // receive byte as a character
    Serial.println(x);         // print the character
  }
        Serial.println("hello");  
        irsend.sendTagShot(0xC83, 14);
          Wire.onReceive(receiveEvent); // register event
   Serial.begin(9600);
         Serial.println("hello");  
}


