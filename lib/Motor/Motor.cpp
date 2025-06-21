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
    case RotationDirection::ROTATION_CW:
        analogWrite(m_PINEN, speed);
        digitalWrite(m_PININ1, HIGH);
        digitalWrite(m_PININ2, LOW);
        break;
    case RotationDirection::ROTATION_CCW:
        analogWrite(m_PINEN, speed);
        digitalWrite(m_PININ1, LOW);
        digitalWrite(m_PININ2, HIGH);
    default:
        break;
    }
}

void Motor::set_state(int speed, MovementDirection dir, Side side) {
    RotationDirection _rotDir;

    if (dir == MovementDirection::MOVE_Forward) {
        if (side == Side::SIDE_Left) _rotDir = ROTATION_CCW;
        else _rotDir = ROTATION_CW;
    }
    else {
        if (side == Side::SIDE_Left) _rotDir = ROTATION_CW;
        else _rotDir = ROTATION_CCW;
    }

    this->set_state(speed, _rotDir);
}

void Motor::stop() {
    digitalWrite(m_PINEN, LOW);
    digitalWrite(m_PININ1, LOW);
    digitalWrite(m_PININ2, LOW);
}