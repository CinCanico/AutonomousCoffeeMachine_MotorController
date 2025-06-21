#include <Arduino.h>
#include <Encoder.h>
#include <math.h>

Encoder::Encoder(uint8_t aPin, uint8_t bPin) {
    m_PINA = aPin;
    m_PINB = bPin;
    m_ENCA = 0;
    m_ENCB = 0;
    m_dir = RotationDirection::ROTATION_CW;
    m_angle = 0;
    m_count = 0;
    m_previousCount = 0;
}

Encoder::~Encoder() {}

void Encoder::setup() {
    pinMode(m_PINA, INPUT);
    pinMode(m_PINB, INPUT);
}

void Encoder::update() {
    m_ENCA = digitalRead(m_PINA);
    m_ENCB = digitalRead(m_PINB);

    if (m_ENCA == m_ENCB) {
        m_count++;
        m_dir = RotationDirection::ROTATION_CW;
        m_angle += 1.0 * 360.0 / CPR;
    }
    else {
        m_count--;
        m_dir = RotationDirection::ROTATION_CCW;
        m_angle -= 1.0 * 360.0 / CPR;
    }

}

RotationDirection Encoder::GetRotationDirection() {
    return m_dir;
}

int Encoder::GetCount() {
    return m_count;
}

int Encoder::GetInterruptPin() {
    return m_PINA;
}

double Encoder::GetAngle() {
    double x = fmod(m_angle, 360);
    if (x < 0)
        x += 360;
    return x;
}

