#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>

#define PIN             6    /* PIN NUMBER OF "matrix" */
#define PIN2            7    /* PIN NUMBER OF "matrix2" */
#define NUMPIXELS       29*7  /* NUMBER OF PIXELS */
#define luminosity      255   /* THE BRIGHTNESS LEVEL OF THE LED's */

int sensorPin = A0;
int sensorValue = 0;

//Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(29, 7, PIN,
//    NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
//    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
//    NEO_GRB            + NEO_KHZ800);

//Adafruit_NeoMatrix matrix2 = Adafruit_NeoMatrix(29, 7, PIN2,
//    NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
//    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
//    NEO_GRB            + NEO_KHZ800);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(7, 29, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

Adafruit_NeoMatrix matrix2 = Adafruit_NeoMatrix(7, 29, PIN2,
                             NEO_MATRIX_BOTTOM  + NEO_MATRIX_LEFT +
                             NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                             NEO_GRB            + NEO_KHZ800);

/* DECLARES COLORS FOR "matrix" */
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(60, 125, 255), matrix2.Color(255, 120, 60), matrix.Color(220, 20, 60), matrix.Color(255, 215, 0)
};

/* DECLARES COLORS FOR "matrix2" */
const uint16_t colors2[] = {
  matrix2.Color(255, 0, 0), matrix2.Color(0, 255, 0), matrix2.Color(60, 125, 255), matrix2.Color(255, 120, 60), matrix.Color(220, 20, 60), matrix.Color(255, 215, 0)
};

class Cycler {
  public:
    void cycle_through(); /* LOOPS THROUGH TRICKS */
    void test() {
      runThrough();
    }
  private:
    void runThrough();
    void tNegative();
    void rainbow();
    void brightnessControl(); /* GETS VALUE FROM SERIAL PORT AND SETS BRIGHTNESS FROM VALUE */
    void zoomin();
    void print_words(char[], int, int); /* TAKES THREE ARGUMENTS: CHAR ARRAY(STRING), COLOR, ADDED TIME TO LOOP */
    void strobe(int); /* TAKES INT FOR TIME TO RUN PRINTS RANDOM WHITE PIXELS */
    void rectangles();
    void circle();
    void random_draw();
    void background();
    void line();    /* PRINTS RANDOM LINES */
    void wait(int); /* WAITS FOR AN ALLOTED AMOUNT OF TIME */
    void random_color(int, int, int, int);
};

void Cycler::cycle_through() {
  matrix.drawPixel(0, 0, matrix.Color(255, 0, 0));
  matrix.drawPixel(6, 0, matrix.Color(0, 255, 0));
  matrix.drawPixel(6, 28, matrix.Color(0, 0, 255));
  //
  matrix2.drawPixel(0, 0, matrix.Color(255, 255, 0));
  matrix2.drawPixel(6, 0, matrix.Color(255, 0, 255));
  matrix2.drawPixel(6, 28, matrix.Color(0, 255, 255));
  //
  matrix.show();
  matrix2.show();
  delay(100000);
  zoomin();
  if ( 1 == random() % 3) {
    print_words("PHYXTGEARS", 1/*green*/, 0);
  }
  else {
    print_words("1720", 1/*green*/, 0);
  }
  strobe(50);
  random_draw();
  rectangles();
  print_words("JUDGES ROCK!", 0/*RED*/, 0);
  runThrough();
  line();
  rainbow();
  print_words("Bling It On!", random() % 5, 0);
  background();
  circle();
  tNegative();
}

void setup() {
  Serial.begin(9600);
  matrix.begin();                    /* RESETS ALL THE PIXELS IN "matrix" */
  matrix2.begin();                   /* RESETS ALL THE PIXELS IN "matrix2" */
  matrix.setBrightness(luminosity);  /* SETS BRIGHTNESS FOR "matrix" */
  matrix2.setBrightness(luminosity); /* SETS BRIGTNESS FOR "matrix2" */
  matrix.setTextWrap(false);
  matrix2.setTextWrap(false);
  matrix.show();
  matrix2.show();
}

void loop() {
  Cycler Array;
  Array.cycle_through();
}
