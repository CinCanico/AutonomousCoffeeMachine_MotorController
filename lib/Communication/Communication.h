#ifndef COMMUNICATION_LIB
#define COMMUNICATION_LIB

#include <comm_commands.h>

class Communication
{
private:
    DirectionCommands m_currentCommand;
    // Read serial functions
    void read();
public:
    Communication();
    ~Communication();

    void setup();
    void update();

    DirectionCommands GetCurrentCommand();


    // Plot Functions
    void plotData(int);
    void plotData(float);
    void plotData(double);
};

#endif
