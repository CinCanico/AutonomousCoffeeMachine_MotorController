#ifndef MOTOR_LIB
#define MOTOR_LIB
#include <Encoder.h>

class Motor
{
private:
    int m_PININ1, m_PININ2, m_PINEN;
    int m_setSpeed;
    RotationDirection m_dir;

public:
    Motor(int, int, int);
    ~Motor();

    void setup();
    void set_state(int, RotationDirection);
};

#endif