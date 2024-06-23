#include "joystick.h"
#include <string>
#include <vector>

/**
 * @brief Constructor for joystick class, creates axies and buttons for each joystick
 *
 * @param numberofjoysticks Number of joysticks
 * @param axis Array of floats representing joystick axis
 * @param button Array of booleans representing joystick buttons
 * @throws None
 **/
Keyboard_ key;
Mouse_ mouse;
/**
 * @brief Constructor for the Joystick class.
 *
 * This constructor initializes the joystick object with the specified number of joysticks,
 * their axes, and buttons.
 *
 * @param numberofjoysticks The number of joysticks.
 * @param axis An array of floats representing the joystick axes.
 * @param button An array of booleans representing the joystick buttons.
 */
Joystick::Joystick(int numberofjoysticks, float axis[], bool button[])
{
    // Loop through each joystick
    for (int i = 0; i < numberofjoysticks; i++)
    {
        // Set the number of buttons and axes per joystick
        int numberofbuttons = i; // Assuming the number of buttons increases with the joystick index
        int numberofaxies = 2;   // Assuming each joystick has two axes (X and Y)

        // Update the total number of buttons and axes
        this->numberofbuttons += numberofbuttons;
        this->numberofaxies += numberofaxies;
    }
}

/**
 * @brief Sets the axis value and determines the corresponding action
 *
 * @param action Array of strings representing the actions
 * @param value Float representing the value of the axis
 * @param isbutton Boolean indicating if it is a button
 */
void Joystick::setaxis(String action[4], float value, bool isbutton, int buttonpin)

{

    // Map value to action
    int whichAction = map(value, 0, 1080, 0, 2);
    if (isbutton)
    {
        if (buttonpin)
        {
            // action for button
            parseAction(action[4]);
        }
    }
    // Parse action based on whichAction
    switch (whichAction)
    {
    case 1:
        parseAction(action[1]);
        break;
    case 2:
        parseAction(action[2]);
        break;
    case 3:
        parseAction(action[3]);
        break;
    default:
        break;
    }
}

/**
 * @brief Parses the action string and performs the corresponding action
 *
 * @param action The action string to parse
 *
 * The action string is expected to have the following format:
 * [action_type]_[keyboard_action]_[action_type]_[action_type]
 *
 * The action type can be one of the following:
 * - key: Indicates that the action is related to keyboard input
 * - mouse: Indicates that the action is related to mouse input
 *
 * The keyboard action can be one of the following:
 * - press: Presses the specified key
 * - release: Releases the specified key
 * - write: Writes the specified key
 *
 * The mouse action can be one of the following:
 * - press: Presse s the specified mouse button
 * - release: Releases the specified mouse button
 * - move: Moves the mouse by the specified amount
 *
 * The key action value is extracted from the action string and converted to an
 * uint8_t.
 *
 * If the action type is "key", the keyboard action is performed. If the action
 * type is "mouse", the mouse action is performed. Otherwise, the action is
 * ignored.
 */
void parseAction(String action)
{
    // Convert action string to a C++ string
    std::string actionString = action.c_str();

    // Find the indices of the underscores in the action string
    int firstUnderscore = actionString.find_first_of("_");                       // Index of the first underscore tells if it is a key or mouse action
    int secondUnderscore = actionString.find_first_of("_", firstUnderscore + 1); // Index of the second underscore, if its key this is part of keyboard action , if mouse move its x and y
    int thirdUnderscore = actionString.find_first_of("_", secondUnderscore + 1); // Index of the third underscore, if its key this is part of keyboard action , if mouse move it is middle mouse scroll
    int fourthUnderscore = actionString.find_first_of("_", thirdUnderscore + 1); // Index of the fourth underscore, indicates action type such as press, release, write for keys or move press , release for mouse

    // Extract the action type from the action string
    std::string actionType = actionString.substr(0, firstUnderscore); // "key" or "mouse"

    // Extract the keyboard action value from the action string
    std::string keyboardAction = actionString.substr(firstUnderscore + 1, secondUnderscore - firstUnderscore - 1);
    uint8_t keyActionValue = static_cast<uint8_t>(std::stoi(keyboardAction));
    if (actionType == "joystick")
    {

        // sets which joystick object to add commands to on secondunderscore, parse
        j
    }
    // Perform the keyboard or mouse action based on the action type
    if (actionType == "key")
    {
        // Perform the keyboard action
        std::string keyboardActionType = actionString.substr(fourthUnderscore + 1); // "press", "release", or "write"

        // Perform the keyboard action based on the action type
        if (keyboardActionType == "press")
        {
            // Press the specified key
            key.press(keyActionValue);
        }
        else if (keyboardActionType == "release")
        {
            // Release the specified key
            key.release(keyActionValue);
        }
        else if (keyboardActionType == "write")
        {
            // Write the specified key
            key.write(keyActionValue);
        }
    }
    else if (actionType == "mouse")
    {
        // Perform the mouse action
        std::string mouseActionType = actionString.substr(fourthUnderscore + 1); // "press", "release", or "move"
        std::string mouseMoveXy = actionString.substr(secondUnderscore + 1, thirdUnderscore - (secondUnderscore + 1));
        std::string mouseMoveMiddle = actionString.substr(thirdUnderscore + 1);
        signed char mouseMoveMiddleInt = static_cast<signed char>(std::stoi(mouseMoveMiddle));

        // Perform the mouse action based on the action type
        if (mouseActionType == "press")
        {
            // Press the specified mouse button
            mouse.press(keyActionValue);
        }
        else if (mouseActionType == "release")
        {
            // Release the specified mouse button
            mouse.release(keyActionValue);
        }
        else if (mouseActionType == "move")
        {
            // Parse mouse movement
            int mouseMoveX = std::stoi(mouseMoveXy.substr(0, mouseMoveXy.find_first_of(".")));
            int mouseMoveY = std::stoi(mouseMoveXy.substr(mouseMoveXy.find_first_of(".") + 1));

            // Move the mouse based on the x and y values, and the middle mouse value
            mouse.move(mouseMoveX, mouseMoveY, mouseMoveMiddleInt);
        }
    }
}

void extractCommands(const std::string &commandList, std::vector<std::string> &actions)
{
    // Initialize the start and end indices of the substring to be extracted.
    std::string::size_type start{0};
    std::string::size_type end{commandList.find(',')};
    size_t index{0};

    // Continue extracting substrings until the end of the string is reached.
    while (end != std::string::npos)
    {
        // Extract the substring between start and end indices.
        actions[index] = commandList.substr(start, end - start);

        // Move the start index to the next position after the comma.
        start = end + 1;

        // Find the next comma, if any.
        end = commandList.find(',', start);
        actions[index] = commandList.substr(start);
        // serial print command list for debugging, number each with index at front
        Serial.print(index);
        Serial.print(": ");

        const char *actionsStr = actions[index].c_str();
        Serial.println(actionsStr);
        // Increment the index for the next action.
        ++index;
    }

    // Extract the last substring, which is after the last comma.
}
