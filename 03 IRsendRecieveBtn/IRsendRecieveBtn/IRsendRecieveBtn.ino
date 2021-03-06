/*
Use a button to send IR shot

 http://www.arduino.cc/en/Tutorial/Button
 */
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
int RECV_PIN = 11; 

IRrecv irrecv(RECV_PIN);

decode_results results;


void setup() {
   Serial.begin(9600);
  // initialize the LED pin as an output:

  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  
  pinMode(buttonPin, INPUT);
  lastfire = millis();
  irrecv.enableIRIn(); // Start the receiver

}


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");

  }
   else if (results->decode_type == TAGSHOT) {
    Serial.print("Decoded TAGSHOT: ");

  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC: ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501: ");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 1; i < count; i++) {
    if (i & 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.write('-');
      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println();
}



void loop() {

     if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }

  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    
         
        if ((millis()-lastfire)>=firerate) {
          shots++;
       irsend.sendTagShot(0xC83, 14);
       irrecv.enableIRIn();
         Serial.print(lastfire, DEC);
          Serial.print(" ");
         Serial.print(shots, DEC);
         
         Serial.print(" Button Pushed \n");
        lastfire = millis();
         }
  }

}
