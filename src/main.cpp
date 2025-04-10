#include <Arduino.h>

#define SERIAL_SPEED 9600
#define SERIAL_DELAY 2000
#define LOOP_DELAY 1000

void setup()
{
  Serial.begin(SERIAL_SPEED);
  delay(SERIAL_DELAY);
}

void loop()
{
  delay(LOOP_DELAY);
}