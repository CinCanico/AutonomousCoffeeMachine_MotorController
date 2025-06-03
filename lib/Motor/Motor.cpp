#include <Arduino.h>
#include <Encoder.h>
#include <Motor.h>

Motor::Motor(int pin_in1, int pin_in2, int pin_en) {
    m_PININ1 = pin_in1;
    m_PININ2 = pin_in2;
    m_PINEN = pin_en;
}

Motor::~Motor() {}

void Motor::setup() {
    pinMode(m_PININ1, OUTPUT);
    pinMode(m_PININ2, OUTPUT);
    pinMode(m_PINEN, OUTPUT);
}
void Motor::set_state(int speed, RotationDirection dir) {
    switch (dir) {
    case RotationDirection::CW:
        analogWrite(m_PINEN, speed);
        digitalWrite(m_PININ1, HIGH);
        digitalWrite(m_PININ2, LOW);
        break;
    case RotationDirection::CCW:
        analogWrite(m_PINEN, speed);
        digitalWrite(m_PININ1, LOW);
        digitalWrite(m_PININ2, HIGH);
    default:
        break;
    }


}