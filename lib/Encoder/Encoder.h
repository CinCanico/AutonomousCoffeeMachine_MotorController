#ifndef ENCODER_LIB
#define ENCODER_LIB

enum RotationDirection {
    CW, CCW
};

class Encoder
{
private:
    int m_PINA, m_PINB;
    uint8_t volatile m_ENCA, m_ENCB;
    RotationDirection m_dir;
    double m_angle;
    int volatile m_count;
    int volatile m_previousCount;
public:
    static const int CPR = 70 * 64;
    Encoder(uint8_t, uint8_t);
    ~Encoder();

    int GetInterruptPin();
    void setup();
    void update();

    RotationDirection GetRotationDirection();
    int GetCount();
    double GetAngle();

};

#endif