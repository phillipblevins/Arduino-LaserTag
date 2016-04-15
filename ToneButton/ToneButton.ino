/*


*/
int buttonState = 0;    
void setup() {

  pinMode(4, INPUT);
  digitalWrite(4, HIGH);  //Set internal pull up resistor
}

void loop() {
  buttonState = digitalRead(4);
    if (buttonState == LOW) {
    //make noise
    noise(500,500);
  } 
}

//================================================================================//
// Noise                                                                          //
// This code generates random tones for DURATION between +300 and -300 of the     //
// FREQency specified.                                                            //
//================================================================================//
void noise(int freq, int duration)  {
int low = freq - 300;
int high = freq + 300;
unsigned long time = millis();
while(millis() - time <= duration)  {
tone(7, random(low, high));
}
noTone(7);
}
