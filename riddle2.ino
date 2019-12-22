//Riddle Box 2 Listens to Riddle Box 1

int green = D4;
int red = D2;
int buttonpin = D5;
unsigned long now = 0;
unsigned long lastPublishedAt; 
int publishAfter = 60000;
bool activated = false;
bool publish_success = false;

//potentiometer interface
int potPin1 = A2;
int potPin2 = A3;
int potPin3 = A4;
int potReading1 = 0;
int potReading2 = 0;
int potReading3 = 0;

int num1 = 0;
int num2 = 0;
int num3 = 0;

//Setting up Servo
Servo myServo;
int angle = 0;
int ServoPin = A5;
String SHREY_DEVICE = "e00fce68f3ec1a95fb53ad4c";

void setup() {
    pinMode ( red, OUTPUT);//Red indicate active state of the device
    pinMode ( green, OUTPUT);//Green indicate if the device has been solved
    pinMode ( buttonpin, INPUT_PULLUP);
    
    digitalWrite(green, LOW);//by default this device is not activated
    digitalWrite(red, LOW);
    
    Particle.variable("num1", num1 );
    Particle.variable("num2", num2 );
    Particle.variable("num3", num3 );
    
    myServo.attach(ServoPin);
    Particle.function("setServoPos", setServoPos);
    Particle.function("actDevice", actDevice);
    Particle.function("resetDev", resetDev);

    Particle.subscribe("diot/2019/shrey/unlock/" + SHREY_DEVICE, unlockDevice);
}

void loop() {
    
    potReading1 = analogRead(potPin1);
    potReading2 = analogRead(potPin2);
    potReading3 = analogRead(potPin3);
    
    num1 = map(potReading1, 0,4095, 0, 10);
    num2 = map(potReading2, 0,4095, 0, 10);
    num3 = map(potReading3, 0,4095, 0, 10);
    
    if (activated) {
        //use button click to simulate puzzle solved
        int buttonState = digitalRead ( buttonpin);
        if (num1 == 9 && num2 == 2 && num3 == 3){//**************************** configure the code here
            digitalWrite ( red, HIGH);
            now = millis();
            puzzleDone();
        }
        unsigned long elapsed = millis() - now;
        
        if( now > 0 && elapsed > 10000 && publish_success){
            digitalWrite(red, LOW);
            publish_success = false;
            now = 0;
            resetDevice();//reset the device after 10 second
        }
    }
}

// void activateDevice(const char *event, const char *data) {
//     digitalWrite(green, HIGH); //activate this device
//     activated = true;
// }

void puzzleDone()
{
  if( lastPublishedAt + publishAfter < millis() )
  {
      String eventName = "diot/2019/austin/unlock/" + System.deviceID();
      publish_success = Particle.publish( eventName );
      lastPublishedAt = millis();
      digitalWrite(green, HIGH); //activate this device
  }

}

void resetDevice() {
    digitalWrite(green, LOW);
    activated = false;
    num1 = 0;
    num2 = 0;
    num3 = 0;
}

int setServoPos(String pos) {
    angle = pos.toInt();
    if (angle < 0) {
        return -1;
    }
    if (angle > 180) {
        return -1;
    }
    
    myServo.write(angle);
    return 0;
}

void unlockDevice(const char *event, const char *data) {
    setServoPos("10");
    actDevice("");
}

int actDevice(String arg) {
    activated = true;
    digitalWrite(red, HIGH);
    setServoPos("10");
    return 0;
}

int resetDev(String arg) {
    activated = false;
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    setServoPos("90");
}
