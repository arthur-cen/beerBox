// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>
#define PIXEL_PIN A5
#define PIXEL_COUNT 24
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

Servo myServo;
int angle = 0;
int ServoPin = D3;
String AUSTIN_DEVICE = "e00fce689c13255696bdc053";

uint32_t gold = strip.Color(255, 215, 0);
uint32_t off = strip.Color(0, 0, 0);


void setup() {
    myServo.attach(ServoPin);
    Particle.function("setServoPos", setServoPos);
    Particle.function("resetDev", resetDev);
    Particle.function("actDevice", actHelp);
    Particle.subscribe("diot/2019/austin/unlock/" + AUSTIN_DEVICE, actDevice);
}

void loop() {
    
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

void actDevice(const char *event, const char *data) {
    Particle.unsubscribe();
    Particle.subscribe("diot/2019/user/unlock/" + System.deviceID(), unlockDevice);
    actHelp("");
}

int actHelp(String arg) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, gold);
        strip.show();
    }
    return 0;
}

void unlockDevice(const char *event, const char *data) {
    setServoPos("10");
    for (int k = 0; k < 3; k ++) {
        for (int i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, gold);
            strip.show();
        }
        delay(500);
        for (int i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, off);
            strip.show();
        }
    }
    //TODO: change the light of the ring
}

int resetDev(String arg) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, off);
        strip.show();
    }
    setServoPos("90");
    Particle.unsubscribe();
    Particle.subscribe("diot/2019/austin/unlock/" + AUSTIN_DEVICE, actDevice);
}
