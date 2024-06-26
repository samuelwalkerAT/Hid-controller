#ifndef joystick_H // Include guards to prevent multiple inclusions
#define joystick_H
#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <sstream>

class Joystick
{
public:
    Joystick(int numberofjoysticks, float axis[], bool button[]);
    void numberofjoysticks(int number);
    void setaxis(String action[4], float value, bool isbutton);
    void setbutton(bool button, int value);

private:
    int numberofjoysticks;
    float axis[6];
    bool button[12];
    int numberofbuttons;
    int numberofaxies;

    Keyboard_ key;
    Mouse_ mouse;
    void parseAction(String actionstring;);
    void getcommands(const std::string &commandList, std::vector<std::string> &actions);

    String actions[2];

    String action[4];

    int map(int value, int in_min, int in_max, int out_min, int out_max);

    bool isStringBlank(String str);

    int whichAction;

    String keyboardaction;

    void parseKeyboardAction(String keyboardaction);
};

#endif;