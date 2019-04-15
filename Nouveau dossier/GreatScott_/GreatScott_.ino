#include "FastLED.h"
#define NUM_LEDS 38
#define DATA_PIN 11
#define CLOCK_PIN 13
unsigned char i;
unsigned char m;
unsigned int wait = 50;
unsigned int wait2 = 500;
bool hall = 0;
CRGB leds[NUM_LEDS];
bool G[8][5] = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
};
bool R[8][5] = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 1, 0, 0, 0},
  {1, 0, 1, 0, 0},
  {1, 0, 0, 1, 0},
  {1, 0, 0, 0, 1},
};
bool A[8][5] = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
};
bool T[8][5] = {
  {1, 1, 1, 1, 1},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
};
bool S[8][5] = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
};
bool C[8][5] = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
};
bool H[8][5] = {
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1}
};

bool E[8][5] = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1}
};

bool L[8][5] =  {
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1}
};

bool O[8][5] = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
};

void setup() {
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  EICRA = 0;
  EICRA |= (1 << ISC10);
  EIMSK = 0;
  EIMSK |= (1 << INT1);
  sei();
  for (int i = 0; i < 38; i++) {
    leds[i] = CRGB ::Black;
  }
  FastLED.show();
}

ISR (INT1_vect) {
  hall = 1;
}

void loop() {
  if (hall == 1) {
    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (G[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);

    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (R[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);

    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (E[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);

    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (A[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);


    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (T[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);


    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (S[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);


    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (C[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);

    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (O[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);

    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (T[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);

    for (m = 0; m < 5; m++) {
      for (i = 0; i < 8; i++) {
        if (T[i][m] == 1) {
          leds[i + 11] = CRGB::Red;
        }
        else {
          leds[i + 11] = CRGB::Black;
        }
      }
      FastLED.show();
      delayMicroseconds(wait);
    }

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);

    for (int i = 11; i < 17; i++) {
      leds[i] = CRGB ::Red;
    }
    leds[18] = CRGB::Red;
    FastLED.show();
    delayMicroseconds(wait);

    for (int i = 0; i < 38; i++) {
      leds[i] = CRGB ::Black;
    }
    FastLED.show();
    delayMicroseconds(wait2);
    hall = 0;
  }
}

