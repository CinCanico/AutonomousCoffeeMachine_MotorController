#include "comm_commands.h"
#include <Arduino.h>


DirectionCommands KeyboardConversion(char *_single_byte, DirectionCommands last) {
    switch ((int)_single_byte) {
    case 'q':
        return DirectionCommands::COM_ForwardLeft;
        break;
    case 'w':
        return DirectionCommands::COM_Forward;
        break;
    case 'e':
        return DirectionCommands::COM_ForwardRight;
        break;
    case 'a':
        return DirectionCommands::COM_Left;
        break;
    case 's':
        return DirectionCommands::COM_Stop;
        break;
    case 'd':
        return DirectionCommands::COM_Right;
        break;
    case 'z':
        return DirectionCommands::COM_BackwardLeft;
        break;
    case 'x':
        return DirectionCommands::COM_Backward;
        break;
    case 'c':
        return DirectionCommands::COM_BackwardRight;
        break;
    default:
        return last;
        break;
    }
}