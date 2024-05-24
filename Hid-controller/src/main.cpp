#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "mouse.h"
#include "Keyboard.h"
#include "Adafruit_CircuitPlayground.h"
// put function declarations here:
// initalize mpu6050 and neopixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);
Adafruit_MPU6050 mpu;
// set up mouse and keyboard
// initalize playground express native button
bool active = false;
int rightButton = 19;
int leftButton = 4;
int activeswitch = 21;
int readingx;
int readingy;
void setup()
{
  // pinMode(activeswitch, INPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Started");
  // set up mpu6050 and neopixel
  pixels.begin();
  // pinMode(rightButton, INPUT_PULLUP);
  Wire.begin();

  // set up mouse and keyboard
  Mouse.begin();
  if (mpu.begin())
  {
    Serial.println("mpu begun");
    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    delay(1000);
  }
  else if (!mpu.begin())
  {
    Serial.println("mpu not begun");
  } // map accelerometer to mouse movement

  // initalize playground express native button

  pixels.setPixelColor(0, 255, 0, 0);
  pixels.show();

  delay(1000);
}

void loop()
{

  // active = digitalRead(activeswitch);
  //  if(!active){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  readingx = map(g.gyro.x, -120, 120, -1000, 1000);
  readingy = map(a.acceleration.y, -8, 8, -100, 100);
  // Serial.print("x,");
  /* Print out the values */ Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  Serial.print(", ");
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);
  Serial.print(",");
  Serial.print("GyroZ:");
  Serial.print(g.gyro.z);
  Serial.println("");
  // take mpu readings and send mouse movement wait for movement greater than offset
  int offset = 1;

  Mouse.move(a.acceleration.x, a.acceleration.y);

  // Mouse.release();
  delay(10);

  // }
}

void fusion360(sensors_event_t a, sensors_event_t g)
{
  // switch case to handle move in fusion 360 3 cases for pan rotate and zoom corrisponding to fusion mouse click movments
  switch (a)
  {
  case break;
      gcjgcjg default:
    break;
  }
}