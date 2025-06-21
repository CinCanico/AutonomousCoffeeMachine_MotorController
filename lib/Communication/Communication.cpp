#include <Arduino.h>
#include <Communication.h>
#include <comm_commands.h>


Communication::Communication(/* args */) {}

Communication::~Communication() {}

void Communication::setup() {
    m_currentCommand = COM_Stop;
    Serial.begin(9600);
    Serial.println("== START ==");
    delay(10);
}

void Communication::update() {
    this->read();
}

DirectionCommands Communication::GetCurrentCommand() {
    return m_currentCommand;
}

void Communication::read() {
    char _Buffer;
    // Check if there is readable messages 
    if (Serial.available() > 0) {
        _Buffer = Serial.read();
        m_currentCommand = KeyboardConversion(_Buffer, m_currentCommand);
        Serial.println(_Buffer);
    }
}

void Communication::plotData(int data) {
    char message[25] = "$";
    char buffer[10];

    strcat(message, itoa(data, buffer, 10));
    strcat(message, ";");
    Serial.println(message);
    Serial.println("");

}
void Communication::plotData(float data) {
    char message[25] = "$";
    char buffer[10];
    dtostrf((double)data, 0, 6, buffer);
    strcat(message, buffer);
    strcat(message, ";");
    Serial.println(message);
    Serial.println("");


}
void Communication::plotData(double data) {
    char message[25] = "$";
    char buffer[10];
    dtostrf(data, 0, 6, buffer);
    strcat(message, buffer);
    strcat(message, ";");
    Serial.println(message);
    Serial.println("");
}