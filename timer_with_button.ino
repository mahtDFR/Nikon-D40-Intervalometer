/*
Nikon D40 Intervalometer
By Matt 
15.10.2016
*/

# define interval 30 //set interval time in seconds

int intervalTime = (interval * 1000); //convert interval from seconds to milliseconds
int IRledPin =  13; // LED connected to digital pin 13
int buttonPin = 2; // push button connected to pin 2
volatile int buttonState = 0;  // variable for reading pushbutton status

void setup() {
  pinMode(IRledPin, OUTPUT); // initialize the IR digital pin as an output:
  pinMode(buttonPin, INPUT); // initialize the button as an input
  attachInterrupt(0, pinISR, CHANGE); // attach an interrupt to the ISR vector
  Serial.begin(9600); // start serial communication for debugging
}

void loop() {
  SendNikonCode(); // fire shutter
  Serial.println("Sending IR signal");// print message on serial monitor
  delay(intervalTime); // wait this amount of time before firing again
}

void pinISR() {
  int val = digitalRead(buttonPin); // read button pin state
  if (val == HIGH) { // if button is pressed
    Serial.println("Sending IR signal"); // print to serial monitor
    SendNikonCode(); // fire shutter
  }
}

// This procedure sends a 38KHz pulse to the IRledPin
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait

  cli();  // this turns off any background interrupts

  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
    digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working

    // so 26 microseconds altogether
    microsecs -= 26;
  }

  sei();  // this turns them back on
}

void SendNikonCode() {
  // This is the code for my particular Nikon, for others use the tutorial
  // to 'grab' the proper code from the remote

  pulseIR(2080);
  delay(27);
  pulseIR(440);
  delayMicroseconds(1500);
  pulseIR(460);
  delayMicroseconds(3440);
  pulseIR(480);


  delay(65); // wait 65 milliseconds before sending it again

  pulseIR(2000);
  delay(27);
  pulseIR(440);
  delayMicroseconds(1500);
  pulseIR(460);
  delayMicroseconds(3440);
  pulseIR(480);
}
