#ifndef joystick_H  // Include guards to prevent multiple inclusions
#define joystick_H
#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
class Joystick
{
public:
Joystick();
void numberofjoysticks(int number);
void setaxis(bool axis, int value );
void setbutton(bool button, int value);
private:
int numberofjoysticks;
int axis[6];
int button[12];


}







#endif