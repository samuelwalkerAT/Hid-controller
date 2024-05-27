#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Mouse.h>
#include <Keyboard.h>
#include <Adafruit_CircuitPlayground.h>
Adafruit_MPU6050 mpu;

enum MovementType
{
  NO_MOVEMENT,
  PAN_RIGHT,
  PAN_LEFT,
  PAN_UP,
  PAN_DOWN,
  ROTATE_CLOCKWISE,
  ROTATE_COUNTERCLOCKWISE,
  ZOOM_IN,
  ZOOM_OUT
};

void setup()
{
  Adafruit_CircuitPlayground CircuitPlayground;
  // Initialize serial communication for debugging purposes
  Serial.begin(115200);
  // initiize mouse and keyboard
  Mouse.begin();
  Keyboard.begin();

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
  const float panThreshold = 5.0;
  const float rotateThreshold = 20.0;
  const float zoomThreshold = 15.0;

  // Determine action based on MPU6050 data
  if (abs(a.acceleration.x) > panThreshold)
  {
    return (a.acceleration.x > 0) ? PAN_RIGHT : PAN_LEFT;
  }
  else if (abs(a.acceleration.y > panThreshold))
  {

    return (a.acceleration.y > 0) ? PAN_UP : PAN_DOWN;
  }
  else if (abs(g.gyro.y) > rotateThreshold)
  {
    return (g.gyro.y > 0) ? ROTATE_CLOCKWISE : ROTATE_COUNTERCLOCKWISE;
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
  Mouse.press(MOUSE_MIDDLE);
  Mouse.move(10, 0, 0); // Move mouse right
  delay(100);
  Mouse.release(MOUSE_MIDDLE);
}

void panLeft()
{
  Serial.println("pan left");
  Mouse.press(MOUSE_MIDDLE);
  Mouse.move(-10, 0, 0); // Move mouse left
  delay(100);
  Mouse.release(MOUSE_MIDDLE);
}
void panUp()
{
  // pan up implimentation
  Serial.println("pan up");
  Mouse.press(MOUSE_MIDDLE);
  Mouse.move(0, 10, 0); // Move mouse right
  delay(100);
  Mouse.release(MOUSE_MIDDLE);
}
void panDown()
{
  // pan down
  Serial.println("pan Down");
  Mouse.press(MOUSE_MIDDLE);
  Mouse.move(0, -10, 0); // Move mouse right
  delay(100);
  Mouse.release(MOUSE_MIDDLE);
}
void rotateClockwise()
{
  Serial.println("rotate clockwise ");
  Keyboard.press(KEY_LEFT_SHIFT);
  Mouse.press(MOUSE_RIGHT);
  Mouse.move(10, 0, 0); // Move mouse right
  delay(100);
  Mouse.release(MOUSE_RIGHT);
  Keyboard.release(KEY_LEFT_SHIFT);
}

void rotateCounterClockwise()
{
  Serial.println("rotate counter ");
  Keyboard.press(KEY_RIGHT_SHIFT);
  Mouse.press(MOUSE_RIGHT);
  Mouse.move(-10, 0, 0); // Move mouse left
  delay(100);
  Mouse.release(MOUSE_RIGHT);
  Keyboard.release(KEY_RIGHT_SHIFT);
}

void zoomIn()
{
  Serial.println("zoom in");
  Keyboard.press(KEY_RIGHT_CTRL);
  Mouse.move(0, 0, 1); // Scroll up
  delay(100);
  Keyboard.release(KEY_RIGHT_CTRL);
}

void zoomOut()
{
  Serial.println("zoom out ");
  Keyboard.press(KEY_RIGHT_CTRL);
  Mouse.move(0, 0, -1); // Scroll down
  delay(100);
  Keyboard.release(KEY_RIGHT_CTRL);
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
  case ROTATE_CLOCKWISE:
    rotateClockwise();
    break;
  case ROTATE_COUNTERCLOCKWISE:
    rotateCounterClockwise();
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
  if (CircuitPlayground.slideSwitch())
  {
    Serial.println("hid active");
    MovementType movement = determineMovement(a, g);
    handleMovement(movement);
    delay(100); // Adjust delay as needed
  }
}
