#include <Arduino.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>

uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
     }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
      }
      WheelPos -= 170;
      return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void Cycler::brightnessControl() {
    sensorValue = analogRead(sensorPin);
    matrix.setBrightness(sensorValue / 4);
    matrix2.setBrightness(sensorValue / 4);
}

void Cycler::rainbow() {
    uint16_t i, j, c, b;
    for(j=0; j<256; j++) {
        for(i=0; i<7; i++) {
            for(c=0; c<29; c++){
                matrix.drawPixel(c, i, Wheel((i * 29 * 2 + c +j) & 255));
                matrix2.drawPixel(c, i, Wheel((i * 29 * 2 + c +j) & 255));
            }
            for(b=29; b >0; b--){
                matrix.drawPixel(b, i, Wheel((i * 29 * 3 - b +j) & 255));
                matrix2.drawPixel(b, i, Wheel((i * 29 * 3 - b +j) & 255));
            }
        }
        delay(10);
        brightnessControl();
        matrix2.show();
        matrix.show();
    }
}

void Cycler::print_words(char phrase[], int color, int time_exclusion) {
    brightnessControl();
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    matrix.setTextColor(colors[color]);
    matrix2.setTextColor(colors2[color]);
    int x = matrix.width();
    int repeat = sizeof(phrase) * 30 + 40 + time_exclusion;
    for(int i = 0; i < 1; i++){
        for(int j = 0; j < repeat; j++){
            matrix.fillScreen(0);
            matrix2.fillScreen(0);
            matrix.setCursor(x, 0);
            matrix2.setCursor(x, 0);
            matrix.print(phrase);
            matrix2.print(phrase);
            if(--x < -72) {
                x = matrix.width();} 
            delay(50);
            brightnessControl();
            matrix.show();
            matrix2.show();
        }
    }
}

void Cycler::zoomin() {
    int a = 29;
    int b = 7;
    for(int i = 0; i < 4; i++){
        matrix.drawRect(i, i, a, b, matrix.Color(random() % 255, random() % 255, random() % 255));
        matrix2.drawRect(i, i, a, b, matrix2.Color(random() % 255, random() % 255, random() % 255));
        delay(100);
        brightnessControl();
        matrix.show();
        matrix2.show();
        a = a - 2;
        b = b - 2;
    }
}
        
void Cycler::rectangles() {
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    for(int j = 0; j < random() % 4; j++){
        int a = 29;
        int b = 7;
        int c = 0;
        for(int i = 0; i < 4; i++){
            matrix.drawRect(i, i, a, b, colors[i]);
            matrix.drawRect(i - 1, i - 1, a + 2, b + 2, matrix.Color(0, 0, 0));
            matrix2.drawRect(i, i, a, b, colors2[i]);
            matrix2.drawRect(i - 1, i - 1, a + 2, b + 2, matrix.Color(0, 0, 0));
            delay(300);
            brightnessControl();
            matrix.show();
            matrix2.show();
            a = a - 2;
            b = b - 2;
        }
        delay(300);
        matrix.fillScreen(matrix.Color(0, 0, 0));
        brightnessControl();
        matrix.show();
        wait(300);
    }
}

void Cycler::circle() {
    int a = -3;
    int b = 3;
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    for(int i = 0; i < 38; i++){
        matrix.drawCircle(a - 1, b, 3, matrix.Color(0, 0, 0));
        matrix2.drawCircle(a - 1, b, 3, matrix.Color(0, 0, 0));
        matrix.drawCircle(a, b, 3, matrix.Color(random() % 255, random() % 255, random() % 255));
        matrix2.drawCircle(a, b, 3, matrix.Color(random() % 255, random() % 255, random() % 255));
        delay(75);
        brightnessControl();
        matrix.show();
        matrix2.show();
        a++;
    }
    wait(50);
}



void Cycler::random_draw() {
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    for(int i = 0; i < 80; i++){
        matrix.drawPixel(random() % 29, random() % 7, matrix.Color(random() % 255, random() % 255, random() % 255));
        matrix2.drawPixel(random() % 29, random() % 7, matrix2.Color(random() % 255, random() % 255, random() % 255));
        delay(50);
        brightnessControl();
        matrix.show();
        matrix2.show();
    }
    wait(50);
}

void Cycler::background() {
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    int a = 14;
    int b = 3;
    int c = 14;
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    for(int i = 0; i < 15; i++){
        matrix.fillScreen(matrix.Color(0, 0, 255));
        matrix.drawCircle(a, b, c, colors[0]);
        matrix2.fillScreen(matrix.Color(0, 0, 255));
        matrix2.drawCircle(a, b, c, colors2[0]);
        delay(100);
        brightnessControl();
        matrix.show();
        matrix2.show();
        c--;
     }
   wait(50);
}

void Cycler::tNegative() {
    matrix.fillScreen(colors[1]);
    matrix2.fillScreen(colors2[1]);
    matrix.show();
    matrix2.show();
    for(int i = 0; i < 7; i = i + 2){
        for(int j = 0; j < 27; j = j = j + 3){
            matrix.drawPixel(j, i, matrix.Color(255, 255, 255));
            matrix2.drawPixel(j, i, matrix.Color(255, 255, 255));
            delay(50);
            brightnessControl(); 
            matrix.show();
            matrix2.show();
            matrix.drawPixel(j, i, colors[1]);
            matrix2.drawPixel(j, i, colors2[1]);
        }
        for(int j = 27; j > 0; j = j - 3){
            matrix.drawPixel(j, i + 1, matrix.Color(255, 255, 255));
            matrix2.drawPixel(j, i + 1, matrix.Color(255, 255, 255));
            delay(50);
            brightnessControl();
            matrix.show();
            matrix2.show();
            matrix.drawPixel(j, i + 1, colors[1]);
            matrix2.drawPixel(j, i + 1, colors2[1]);
        }
    }
}

void Cycler::line() {
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    int a = 0;
    for(int i = 0; i < 50; i++){
        matrix.drawLine(random() % 29, random() % 7, random() % 29, random() % 29, matrix.Color(random() % 255, random() % 255, random() % 255));
        matrix2.drawLine(random() % 29, random() % 7, random() % 29, random() % 29, matrix2.Color(random() % 255, random() % 255, random() % 255));
        delay(50);
        brightnessControl();
        matrix.show();
        matrix2.show(); 
    }
    wait(300);
}
        
void Cycler::wait(int Wait){
    for(int i = 0; i < 1; i++){
        delay(Wait);
    }
}
    

void Cycler::runThrough() {
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix2.fillScreen(matrix2.Color(0, 0, 0));
    for(int i = 0; i < 7; i = i + 2){
        for(int j = 0; j < 27; j++){
            matrix.drawPixel(j, i, colors[2]);
            matrix2.drawPixel(j, i, colors2[2]);
            brightnessControl();
            delay(10);
            matrix.show();
            matrix2.show();
            matrix.drawPixel(j, i, matrix.Color(0, 0, 0)); 
            matrix2.drawPixel(j, i, matrix2.Color(0, 0, 0));   
        }
        for(int j = 27; j > 0; j--){
            matrix.drawPixel(j, i + 1, colors[2]);   
            matrix2.drawPixel(j, i + 1, colors2[2]);
            brightnessControl();
            delay(10);
            matrix.show();
            matrix2.show();
            matrix.drawPixel(j, i + 1, matrix.Color(0, 0, 0)); 
            matrix2.drawPixel(j, i + 1, matrix2.Color(0, 0, 0));   
        }
    }
}

void Cycler::strobe(int Time) {
    //clearScreen();
    for(int j = 0; j < Time; j++){
        for(int i = 0; i < 1; i++){
            matrix.drawPixel(random() % 29, random() % 7, matrix.Color(255, 255, 255));
            matrix2.drawPixel(random() % 29, random() % 7, matrix.Color(255, 255, 255));
            delay(50);
            brightnessControl();
            matrix.show();
            matrix2.show();
        }
        matrix.fillScreen(matrix.Color(0, 0, 0));
        matrix2.fillScreen(matrix2.Color(0, 0, 0));
        delay(0);
        matrix.show();
        matrix2.show();
    }
}
        
