//Lib esp32_digital_led_lib
#include "esp32_digital_led_lib.h"
#define min(m,n) ((m)<(n)?(m):(n))

#define NUM_STRIPS 6
#define NUM_LEDS_PER_STRIP 56

#define TEST_VAL 10
#define CORRECTOR -1

// LEDS settings
int PINS[NUM_STRIPS] = {23, 22, 18, 5, 21, 19};

const int numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP * 3;
const int numberOfLed = NUM_STRIPS * NUM_LEDS_PER_STRIP ;

void gpioSetup(int gpioNum, int gpioMode, int gpioVal) {
#if defined(ARDUINO) && ARDUINO >= 100
  pinMode (gpioNum, gpioMode);
  digitalWrite (gpioNum, gpioVal);
#elif defined(ESP_PLATFORM)
  gpio_num_t gpioNumNative = static_cast<gpio_num_t>(gpioNum);
  gpio_mode_t gpioModeNative = static_cast<gpio_mode_t>(gpioMode);
  gpio_pad_select_gpio(gpioNumNative);
  gpio_set_direction(gpioNumNative, gpioModeNative);
  gpio_set_level(gpioNumNative, gpioVal);
#endif
}// gpioSetup


strand_t STRANDS[NUM_STRIPS];
strand_t * strands [] = { &STRANDS[0], &STRANDS[1], &STRANDS[2], &STRANDS[3], &STRANDS[4], &STRANDS[5] };

void leds_init() {

  for (int k = 0; k < NUM_STRIPS; k++) {
    STRANDS[k] = {  .rmtChannel = k, .gpioNum = PINS[k], .ledType = LED_WS2812B_V3, .brightLimit = 32,
                    .numPixels = NUM_LEDS_PER_STRIP, .pixels = nullptr, ._stateVars = nullptr
                 };
    gpioSetup(PINS[k], OUTPUT, LOW);
  }

  int STRANDCNT = sizeof(STRANDS) / sizeof(STRANDS[0]);

  if (digitalLeds_initStrands(STRANDS, STRANDCNT)) {
#ifdef DEBUG
    Serial.println("Init FAILURE: halting");
    delay(1000);
#endif
    ESP.restart();
  }
  for (int i = 0; i < STRANDCNT; i++)
    strand_t * pStrand = &STRANDS[i];

#ifdef DEBUG
  Serial.println("Init complete");
#endif
}//leds_init


void leds_set(unsigned char* payload) {
  if (payload[1] > NUM_STRIPS) return;

#ifdef DEBUG
  Serial.print("set payload...");
#endif
  byte strip = payload[1] - 1;
  int maxLength = min(NUM_LEDS_PER_STRIP, (MTUu - 4) / 3);

  for (int k = 0; k < maxLength; k += 1)
    //    strands[strip]->pixels[k] = pixelFromRGB(payload[(k * 3) + 2] + CORRECTOR, payload[(k * 3) + 3] + CORRECTOR, payload[(k * 3) + 4] + CORRECTOR);
    strands[strip]->pixels[k] = pixelFromRGB( leds_square(payload[(k * 3) + 2]), leds_square(payload[(k * 3) + 3]), leds_square(payload[(k * 3) + 4]) );

#ifdef DEBUG
  Serial.println("done");
#endif
}


void leds_show() {
  for (int k = 0; k < NUM_STRIPS; k++) {
    digitalLeds_updatePixels(strands[k]);
    yield();
  }
}//leds_show


void leds_test() {
#ifdef DEBUG
  Serial.println("initTest()");
#endif
  for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
    strands[0]->pixels[i] = pixelFromRGB(TEST_VAL, 0, 0);
    strands[1]->pixels[i] = pixelFromRGB(TEST_VAL, 0, 0);
    strands[2]->pixels[i] = pixelFromRGB(TEST_VAL, 0, 0);
    strands[3]->pixels[i] = pixelFromRGB(TEST_VAL, 0, 0);
    strands[4]->pixels[i] = pixelFromRGB(TEST_VAL, 0, 0);
    strands[5]->pixels[i] = pixelFromRGB(TEST_VAL, 0, 0);
  }//for i
  leds_show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
    strands[0]->pixels[i] = pixelFromRGB(0, TEST_VAL, 0);
    strands[1]->pixels[i] = pixelFromRGB(0, TEST_VAL, 0);
    strands[2]->pixels[i] = pixelFromRGB(0, TEST_VAL, 0);
    strands[3]->pixels[i] = pixelFromRGB(0, TEST_VAL, 0);
    strands[4]->pixels[i] = pixelFromRGB(0, TEST_VAL, 0);
    strands[5]->pixels[i] = pixelFromRGB(0, TEST_VAL, 0);
  }//for i
  leds_show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
    strands[0]->pixels[i] = pixelFromRGB(0, 0, TEST_VAL);
    strands[1]->pixels[i] = pixelFromRGB(0, 0, TEST_VAL);
    strands[2]->pixels[i] = pixelFromRGB(0, 0, TEST_VAL);
    strands[3]->pixels[i] = pixelFromRGB(0, 0, TEST_VAL);
    strands[4]->pixels[i] = pixelFromRGB(0, 0, TEST_VAL);
    strands[5]->pixels[i] = pixelFromRGB(0, 0, TEST_VAL);
  }//for i
  leds_show();
  delay(500);
  black_out();
  leds_show();
}//initest

void black_out() {
  byte value = 0;
  for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
    for (int j = 0 ; j < 6 ; j++) {
      strands[j]->pixels[i] = pixelFromRGB(value, value, value);
    }
  }//for i
}//black_out

void w1_out() {
  byte value = 127;
  for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
    for (int j = 0 ; j < 6 ; j++) {
      strands[j]->pixels[i] = pixelFromRGB(value, value, value);
    }
  }//for i
}//w1_out

void loop_led(){
  byte valuea = 100;
  for (int i = 0; i < 56; i++) {
    black_out();
    leds_show();
    for (int j = 0 ; j < 6 ; j++) {
      strands[j]->pixels[i] = pixelFromRGB(valuea, valuea, valuea);
    }
//    delayMicroseconds(500);
    //  w1_out();
    leds_show();
  }
}
byte leds_square(byte value) {
  return (((value + CORRECTOR) * (value + CORRECTOR)) / 255);
}
