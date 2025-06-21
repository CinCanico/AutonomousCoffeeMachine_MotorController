#ifndef COMM_COMMANDS_LIB
#define COMM_COMMANDS_LIB


typedef enum DirectionCommands {
    COM_ForwardLeft, COM_Forward, COM_ForwardRight,
    COM_Left, COM_Stop, COM_Right,
    COM_BackwardLeft, COM_Backward, COM_BackwardRight
} DirectionCommands;

enum DirectionCommands KeyboardConversion(char *, DirectionCommands last);


#endif