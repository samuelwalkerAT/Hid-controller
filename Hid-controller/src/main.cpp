#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Mouse.h>
#include <Keyboard.h>
#include <Adafruit_CircuitPlayground.h>

Adafruit_MPU6050 mpu;
Adafruit_CircuitPlayground Play;
bool debug = 0; // set true for debug

int rotX = A3;
int rotY = A3;

enum MovementType
{
  NO_MOVEMENT,
  PAN_RIGHT,
  PAN_LEFT,
  PAN_UP,
  PAN_DOWN,
  ROTATE_CLOCKWISE,
  ROTATE_COUNTERCLOCKWISE,
  ROTATE_UP,
  ROTATE_DOWN,
  ZOOM_IN,
  ZOOM_OUT
};

void setup()
{
  pinMode(rotX, INPUT);
  pinMode(rotY, INPUT);
  Play.begin();
  // Initialize serial communication for debugging purposes
  Serial.begin(115200);
  // initiize mouse and keyboard
  Mouse.begin();
  Keyboard.begin();
  Serial.println("mouse and keyboard initialized");
  // Initialize MPU6050
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }

  // Set accelerometer range and filter bandwidth
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}
MovementType determineMovement(sensors_event_t a, sensors_event_t g)
{
  // Define thresholds for actions
  const float panThreshold = 3.0;
  const float rotateThreshold = 523.0;
  const float zoomThreshold = 12.0;

  // Determine action based on MPU6050 data
  if (abs(a.acceleration.x) > panThreshold)
  {
    return (a.acceleration.x > 0) ? PAN_RIGHT : PAN_LEFT;
  }
  else if (abs(a.acceleration.y > panThreshold))
  {

    return (a.acceleration.y > 0) ? PAN_UP : PAN_DOWN;
  }
  else if (analogRead(rotX) > rotateThreshold + 50)
  {
    //return ROTATE_COUNTERCLOCKWISE;
  }
  else if (analogRead(rotX) < rotateThreshold - 50)
  {

    //return ROTATE_CLOCKWISE;
  }
  else if (analogRead(rotY) > rotateThreshold + 50)
  {
    return ROTATE_UP;
  }
  else if (analogRead(rotY) < rotateThreshold - 50)
  {
    return ROTATE_DOWN;
  }
  else if (abs(a.acceleration.z) > zoomThreshold)
  {
    return (a.acceleration.z > 0) ? ZOOM_IN : ZOOM_OUT;
  }
  else
  {
    return NO_MOVEMENT;
  }
}

void panRight()
{
  Serial.println("pan right");
  if (!debug)
  {
    Mouse.press(MOUSE_MIDDLE);
    Mouse.move(10, 0, 0); // Move mouse right
    delay(100);
    Mouse.release(MOUSE_MIDDLE);
  }
}

void panLeft()
{
  Serial.println("pan left");
  if (!debug)
  {
    Mouse.press(MOUSE_MIDDLE);
    Mouse.move(-10, 0, 0); // Move mouse left
    delay(100);
    Mouse.release(MOUSE_MIDDLE);
  }
}
void panUp()
{
  // pan up implimentation
  Serial.println("pan up");
  if (!debug)
  {
    Mouse.press(MOUSE_MIDDLE);
    Mouse.move(0, 10, 0); // Move mouse right
    delay(100);
    Mouse.release(MOUSE_MIDDLE);
  }
}
void panDown()
{
  // pan down
  Serial.println("pan Down");
  if (!debug)
  {
    Mouse.press(MOUSE_MIDDLE);
    Mouse.move(0, -10, 0); // Move mouse right
    delay(100);
    Mouse.release(MOUSE_MIDDLE);
  }
}
void rotateClockwise()
{
  Serial.println("rotate clockwise ");
  if (!debug)
  {
    Keyboard.press(KEY_LEFT_SHIFT);
    Mouse.press(MOUSE_MIDDLE);
    Mouse.move(10, 0, 0); // Move mouse right
    delay(10);
    Mouse.release(MOUSE_MIDDLE);
    Keyboard.release(KEY_LEFT_SHIFT);
  }
}

void rotateCounterClockwise()
{
  Serial.println("rotate counter ");
  if (!debug)
  {
    Keyboard.press(KEY_RIGHT_SHIFT);
    Mouse.press(MOUSE_MIDDLE);
    Mouse.move(-10, 0, 0); // Move mouse left
    delay(10);
    Mouse.release(MOUSE_MIDDLE);
    Keyboard.release(KEY_RIGHT_SHIFT);
  }
}
void rotateUp()
{
  Serial.println("rotate up");
  if (!debug)
  {

    Keyboard.press(KEY_RIGHT_SHIFT);
    Mouse.press(MOUSE_MIDDLE);
    Mouse.move(0, 10, 0); // Move mouse left
    delay(10);
    Mouse.release(MOUSE_MIDDLE);
    Keyboard.release(KEY_RIGHT_SHIFT);
  }
  }
  void rotateDown(){
    Serial.println("rotate down");
    if (!debug)
    {
      Keyboard.press(KEY_RIGHT_SHIFT);
      Mouse.press(MOUSE_MIDDLE);
      Mouse.move(0, -10, 0); // Move mouse left
      delay(10);
      Mouse.release(MOUSE_MIDDLE);
      Keyboard.release(KEY_RIGHT_SHIFT);
    }
  }

  void zoomIn()
  {

    Serial.println("zoom in");
    if (!debug)
    {
      // Keyboard.press(KEY_RIGHT_CTRL);
      Mouse.move(0, 0, 1); // Scroll up
      delay(100);
      // Keyboard.release(KEY_RIGHT_CTRL);
    }
  }

  void zoomOut()
  {
    Serial.println("zoom out ");
    if (!debug)
    {
      // Keyboard.press(KEY_RIGHT_CTRL);
      Mouse.move(0, 0, -1); // Scroll down
      delay(100);
      // Keyboard.release(KEY_RIGHT_CTRL);
    }
  }
  void handleMovement(MovementType movement)
  {
    switch (movement)
    {
    case PAN_RIGHT:
      panRight();
      break;
    case PAN_LEFT:
      panLeft();
      break;

    case PAN_UP:
      panUp();
      break;
    case PAN_DOWN:
      panDown();
      break;
    case ROTATE_CLOCKWISE:
      rotateClockwise();
      break;
    case ROTATE_COUNTERCLOCKWISE:
      rotateCounterClockwise();
      break;
    case ROTATE_UP:
      rotateUp();
      break;
    case ROTATE_DOWN:
      rotateDown();
      break;
    case ZOOM_IN:
      zoomIn();
      break;
    case ZOOM_OUT:
      zoomOut();
      break;
    case NO_MOVEMENT:
      // No action needed
      break;
    }
  }
  void loop()
  {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    // if circuit playground switch is on use device as mouse
    Serial.print("rotx:");
    Serial.println(analogRead(rotX));
    // delay(1000);
    if (!Play.slideSwitch())
    {
      Mouse.begin();
      Serial.println("hid active");
      Serial.print("debug");
      Serial.println(debug);
      MovementType movement = determineMovement(a, g);
      handleMovement(movement);
      delay(100); // Adjust delay as needed
    }
    else
    {
      Mouse.end();
      // Serial.print("hid not active");
      // Serial.print("debug");
      // Serial.println(debug);
      delay(100);
    }
  }
