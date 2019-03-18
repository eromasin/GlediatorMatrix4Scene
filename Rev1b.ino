//  Code developed by Liam Weight
//  First Rev - 11/03/19
//  Current Rev - 14/03/19
//

#include <FastLED.h>
#include <SPI.h>
#include <SD.h>

#define LED_PIN 8
#define SENSOR_PIN1 7
#define SENSOR_PIN2 6
#define SENSOR_PIN3 5
#define SENSOR_PIN4 4
#define NUM_LEDS 256
#define CHIPSET WS2812
#define CMD_NEW_DATA 4
#define BAUD_RATE 115200

int sensorState1 = HIGH;
int sensorState2 = HIGH;
int sensorState3 = HIGH;
int sensorState4 = HIGH;

//char* triggerAnimation[] = {"anim1.dat", "anim2.dat", "anim3.dat", "anim4.dat", "startup.dat"};

File idlefxdata;
File fxdata;
CRGB leds [NUM_LEDS];

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, GRB>(leds, NUM_LEDS); //se doc for different LED strips
  Serial.begin(BAUD_RATE);
  for (int y = 0 ; y < NUM_LEDS ; y++)
  {
    leds[y] = CRGB::Black; // set all leds to black during setup
  }
  FastLED.show();
  pinMode(10, OUTPUT);                // CS/SS pin as output for SD library to work.
  digitalWrite(10, HIGH);             // workaround for sdcard failed error...
  pinMode(53, OUTPUT);
  pinMode(SENSOR_PIN1, INPUT_PULLUP);
  pinMode(SENSOR_PIN2, INPUT_PULLUP);
  pinMode(SENSOR_PIN3, INPUT_PULLUP);
  pinMode(SENSOR_PIN4, INPUT_PULLUP);
  delay(500);

  if (!SD.begin(53)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  fxdata = SD.open("startup.dat");  // read only
  if (fxdata) {
    Serial.println("SD card initialization done.");
    for (int i = 0; i <= 50; i++) {
      fxdata.readBytes((char*)leds, NUM_LEDS * 3);
      FastLED.show();
      delay(50); // set the speed of the animation. 20 is appx ~ 500k bauds
    }
    fxdata.close();
  }
  sensorState1 = digitalRead(SENSOR_PIN1);
  sensorState2 = digitalRead(SENSOR_PIN2);
  sensorState3 = digitalRead(SENSOR_PIN3);
  sensorState4 = digitalRead(SENSOR_PIN4);
  Serial.println("Setup sequence complete :)");
}


void loop() {
  checkSensor();
  
  if (sensorState1 == LOW) {
    idlefxdata.close();
    while (sensorState2 == HIGH && sensorState3 == HIGH && sensorState4 == HIGH) {
      Anim1();
      checkSensor2();
      checkSensor3();
      checkSensor4();
    }
  }
  else if (sensorState2 == LOW) {
    idlefxdata.close();
    while (sensorState1 == HIGH && sensorState3 == HIGH && sensorState4 == HIGH) {
      Anim2();
      checkSensor1();
      checkSensor3();
      checkSensor4();
    }
  }
  else if (sensorState3 == LOW) {
    idlefxdata.close();
    while (sensorState1 == HIGH && sensorState2 == HIGH && sensorState4 == HIGH) {
      Anim3();
      checkSensor1();
      checkSensor2();
      checkSensor4();
    }
  }
  else if (sensorState4 == LOW) {
    idlefxdata.close();
    while (sensorState1 == HIGH && sensorState2 == HIGH && sensorState3 == HIGH) {
      Anim4();
      checkSensor1();
      checkSensor2();
      checkSensor3();
    }
  }
  else {
    /*idlefxdata.close();
    fxdata = SD.open("idle.dat");
    while (fxdata.available() && sensorState1 == HIGH && sensorState2 == HIGH && sensorState3 == HIGH && sensorState4 == HIGH) {
      fxdata.readBytes((char*)leds, NUM_LEDS * 3);
      FastLED.show();
      delay(5); // set the speed of the animation. 20 is appx ~ 500k bauds
      checkSensor();
    }
    fxdata.close(); */
  }
  return;
}

void checkSensor1() {
  sensorState1 = digitalRead(SENSOR_PIN1);
}

void checkSensor2() {
  sensorState2 = digitalRead(SENSOR_PIN2);
}

void checkSensor3() {
  sensorState3 = digitalRead(SENSOR_PIN3);
}

void checkSensor4() {
  sensorState4 = digitalRead(SENSOR_PIN4);
}

void checkSensor() {
  checkSensor1();
  checkSensor2();
  checkSensor3();
  checkSensor4();
}


void Anim1() {
  fxdata = SD.open("anim1.dat");
  if (fxdata)
  {
    Serial.println("file 1 open ok");
  }
  while (fxdata.available() && sensorState2 == HIGH && sensorState3 == HIGH && sensorState4 == HIGH)
  {
    fxdata.readBytes((char*)leds, NUM_LEDS * 3);
    FastLED.show();
    delay(50); // set the speed of the animation. 20 is appx ~ 500k bauds
  }
  fxdata.close();
}

void Anim2() {
  fxdata = SD.open("anim2.dat");  // read only
  if (fxdata)
  {
    Serial.println("file 2 open ok");
  }
  while (fxdata.available() && sensorState1 == HIGH && sensorState3 == HIGH && sensorState4 == HIGH)
  {
    fxdata.readBytes((char*)leds, NUM_LEDS * 3);
    FastLED.show();
    delay(50); // set the speed of the animation. 20 is appx ~ 500k bauds
  }
  fxdata.close();
}

void Anim3() {
  fxdata = SD.open("anim3.dat");  // read only
  if (fxdata)
  {
    Serial.println("file 3 open ok");
  }
  while (fxdata.available() && sensorState1 == HIGH && sensorState2 == HIGH && sensorState4 == HIGH)
  {
    fxdata.readBytes((char*)leds, NUM_LEDS * 3);
    FastLED.show();
    delay(50); // set the speed of the animation. 20 is appx ~ 500k bauds
  }
  fxdata.close();
}

void Anim4() {
  fxdata = SD.open("anim4.dat");  // read only
  if (fxdata)
  {
    Serial.println("file 4 open ok");
  }
  while (fxdata.available() && sensorState1 == HIGH && sensorState2 == HIGH && sensorState3 == HIGH)
  {
    fxdata.readBytes((char*)leds, NUM_LEDS * 3);
    FastLED.show();
    delay(50); // set the speed of the animation. 20 is appx ~ 500k bauds
  }
  fxdata.close();
}

