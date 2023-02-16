#include <FastLED.h>
#include <stdlib.h>

#define DATA_PIN 7
#define NUM_LEDS 144

CRGB leds[NUM_LEDS];

void setup() {

  Serial.begin(9600);
  Serial.println("Started");

  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);

  FastLED.setBrightness(10);

}

void loop() {

  int sensorValue0 = analogRead(A0); //analog voltage 2.5 +- 1.2 = 1.3 to 3.7
  float voltage0 = sensorValue0 * (5.0 / 1023.0);
  Serial.print("A0: ");
  Serial.print(voltage0);
  Serial.print("   xValue: ");
  int xValue = int((voltage0 - 1.3) * 100);
  Serial.print(xValue);


  int sensorValue1 = analogRead(A1); //analog voltage 2.5 +- 1.2 = 1.3 to 3.7
  float voltage1 = sensorValue1 * (5.0 / 1023.0);
  Serial.print("     A1: ");
  Serial.print(voltage1);
  Serial.print("   yValue: ");
  int yValue = int((voltage1 - 1.3) * 100);
  Serial.print(yValue);

  int sensorValue2 = analogRead(A2); //analog voltage .4 to 4.9
  float voltage2 = sensorValue2 * (5.0 / 1023.0);
  Serial.print("     A2: ");
  Serial.print(voltage2);
  Serial.print("   potValue: ");
  int potValue = int((voltage2 - .4) * 56); //potentiometer value controls brightness of leds
  Serial.println(potValue);

  FastLED.setBrightness(clampValue(potValue));

  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(clampValue(xValue), 130, clampValue(yValue));
    FastLED.show();
  }

}

int clampValue(int value){
  if(value > 0 && value <255){
    return value;
  }
  else if(value < 0){
    return 0;
  }
  else if(value > 255){
    return 255;
  }
}
