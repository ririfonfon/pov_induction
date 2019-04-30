#include <Adafruit_DotStar.h>
#include <QTRSensors.h>
#include <SPI.h>
#include "graphics.h"
volatile int numRot = 0;
int numDiv = 0;
int stateDiv = 0;
uint32_t color;
volatile unsigned long rotTime, timeOld, timeNow, opeTime;

#define DATAPIN    MOSI
#define CLOCKPIN   SCK
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);

//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BGR);
void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  strip.begin(); // Initialize pins for output
  strip.show();
  attachInterrupt(digitalPinToInterrupt(D2), RotCount, FALLING );
  opeTime = millis();
  Serial.println("setup ok");
  for (int i = 0; i <= NUMPIXELS; i++) {
    strip.setPixelColor(i, 5, 0, 0);
  }
  strip.show();
  delay(200);
  for (int i = 0; i <= NUMPIXELS; i++) {
    strip.setPixelColor(i, 0, 5, 0);
  }
  strip.show();
  delay(200);
  for (int i = 0; i <= NUMPIXELS; i++) {
    strip.setPixelColor(i, 0, 0, 5);
  }
  strip.show();
  delay(200);
  for (int i = 0; i <= NUMPIXELS; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
  Serial.println("strip ok");
}
void loop() {

//  if (stateDiv == 1 && micros() - timeOld > rotTime / Div * (numDiv)) {
//    stateDiv = 0;
////    Serial.println("stateDiv = 0;");
//  }
//  if (stateDiv == 0 && micros() - timeOld < rotTime / Div * (numDiv + 1)) {
//    stateDiv = 1;
//    Serial.println("stateDiv = 1;");
    strip.clear();
    if (2000 > millis() - opeTime) {
      color = strip.Color(5, 0, 0);
    } else if (4000 > millis() - opeTime) {
      color = strip.Color(0, 5, 0);
    } else if (6000 > millis() - opeTime) {
      color = strip.Color(0, 0, 5);
    } else {
      color = strip.Color(5, 5, 0);
    }

    if (8000 <= millis() - opeTime) opeTime = millis();
    
    numDiv++;
    if (numDiv >= Div ) numDiv = 0;

          for (int i = 0; i <= NUMPIXELS; i++) {
      if (pgm_read_byte_near(&dvd[numDiv][i]) == 1) {
        strip.setPixelColor(i, color);
      }
    }
    strip.show();
//  }
}
void RotCount() {
  timeNow = micros();
  rotTime = timeNow - timeOld;
  timeOld = timeNow;
  numRot++;
  if (numRot >= Div ) numRot = 0;
}
