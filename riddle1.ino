// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h> //note this CANNOT be pasted. Must be installed from Library

#define PIXEL_PIN D2
#define PIXEL_COUNT 4
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
int b1Pin = D3;
int b2Pin = D4;
int b3Pin = D5;
int b4Pin = D6;
int b1State = 0;
int b2State = 0;
int b3State = 0;
int b4State = 0;
int b1Value;
int b2Value;
int b3Value;
int b4Value;

//Timing variables
unsigned long prevMillis1 = 0;
unsigned long prevMillis2 = 0;
unsigned long prevMillis3 = 0;
unsigned long prevMillis4 = 0;
unsigned long timeElapsed1 = 0;
unsigned long timeElapsed2 = 0;
unsigned long timeElapsed3 = 0;
unsigned long timeElapsed4 = 0;
unsigned long btnInterval = 500;

//establish color codes
uint32_t white = strip.Color(240, 240, 240);
uint32_t red = strip.Color(255, 0, 10);

//Setup the status LED 
int greenLED = A0;
int redLED = A1;
unsigned long lastPublishedAt = 0;
unsigned long elapsed = 0;
int publishAfter = 60000;//listener will re-activated after 60 seconds
bool publish_success = false;

void setup() {
    //set the pin modes
    pinMode (b1Pin, INPUT_PULLUP);
    pinMode (b2Pin, INPUT_PULLUP);
    pinMode (b3Pin, INPUT_PULLUP);
    pinMode (b4Pin, INPUT_PULLUP);
    
    //create the partical variables for debugging purposes
    Particle.variable("button1", b1State);
    Particle.variable("button2", b2State);
    Particle.variable("button3", b3State);
    Particle.variable("button4", b4State);
    
    //turn on the strip
    strip.begin();
    //cycle through pixels, turn each to white
    for (int i = 0; i < 4; i++) {
        strip.setPixelColor(i, white);
    }
    strip.show(); //show the color
    prevMillis1 = millis();
    prevMillis2 = millis();
    prevMillis3 = millis();
    prevMillis4 = millis();
    
    //activate box
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
}

void loop() {
    //read the buttons
    b1Value = digitalRead(b1Pin);
    b2Value = digitalRead(b2Pin);
    b3Value = digitalRead(b3Pin);
    b4Value = digitalRead(b4Pin);
    //calculate timeElapsed since last button pressed
    timeElapsed1 = millis() - prevMillis1;
    timeElapsed2 = millis() - prevMillis2;
    timeElapsed3 = millis() - prevMillis3;
    timeElapsed4 = millis() - prevMillis4;
    //check if button 1 pressed
    //Only when the time interval between two button press is greater than the threshold, we count it as on press
    if (b1Value == LOW && timeElapsed1 > btnInterval) { 
        prevMillis1 = millis();
        if (b1State < 1) {
            b1State = 1;
            strip.setPixelColor(0, red);
        } else {
            b1State = 0;
            strip.setPixelColor(0, white);
        }
        strip.show();
    }
    //check if button 2 pressed
    if (b2Value == LOW && timeElapsed2 > btnInterval) {
        prevMillis2 = millis();
        if (b2State < 1){
            b2State = 1;
            strip.setPixelColor(1, red);
        } else {
            b2State = 0;
            strip.setPixelColor(1, white);
        }
        strip.show();
    }
    //check if button 3 pressed
    if (b3Value == LOW && timeElapsed3 > btnInterval) {
        prevMillis3 = millis();
        if (b3State < 1 ) {
            b3State = 1;
            strip.setPixelColor(2, red);
        }
        else{
            b3State = 0;
            strip.setPixelColor(2, white);
        }
        strip.show();
    }
    //check if button 4 pressed
    if(b4Value == LOW && timeElapsed4 > btnInterval) {
        prevMillis4 = millis();
        if (b4State < 1) {
            b4State = 1;
            strip.setPixelColor(3, red);
        } else {
            b4State = 0;
            strip.setPixelColor(3, white);
        }
        strip.show();
    }
    //verify the answer, do only when the unlock event is not published
    if (checkAnswer() && !publish_success) {
        puzzleDone();
        digitalWrite(greenLED, HIGH);
    }
    
    elapsed = millis() - lastPublishedAt;
    if( lastPublishedAt > 0 && elapsed > publishAfter && publish_success){
        digitalWrite(greenLED, LOW);
        publish_success = false;
        lastPublishedAt = 0;
    }
}//end the code

int checkAnswer( ) {
    //answer is <0 1 1 0>
    if (!b1State && b2State && b3State && !b4State) {
        return 1;
    }
    return 0;
}

void puzzleDone() {
      String eventName = "diot/2019/shrey/unlock/" + System.deviceID();
      publish_success = Particle.publish( eventName );
      lastPublishedAt = millis();
}
