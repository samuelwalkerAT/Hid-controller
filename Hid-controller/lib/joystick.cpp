#inclue joystick.h

joystick::joystick(int numberofjoysticks, float axis[], bool button[])
{

    // create two axies and one button for each joystick
    for (int i = 0; i < numberofjoysticks; i++)
    {

        int numberofbuttons = i;
        int numberofaxies = i++;

        // set number of axies and buttons
        this->numberofjoysticks = numberofjoysticks;
        this->numberofbuttons = numberofbuttons;
        this->numberofaxies = numberofaxies;
        // set axies and buttons
    }
}

void joystick::setaxis(string action[4], float value, bool isbutton)
{
    // take string and create series of mouse movements and or key strokes
    // map values to number of actions available if 3 actions are available value has 3 extremes and 3 buttons
    int whichAction = map(value, 0, 1080, 0, 2);
    // parse string actions commas between actions if mouse map to axies

    switch (whichAction)
    {
    case 1:
        // parse action 1
        break;

    default:
        break;
    }
}

void parseAction(string action)
{
    //
    sscanf(action, "%s,%s,%s,%d,%d", type, direction, key, );
}