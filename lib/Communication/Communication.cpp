#include <Communication.h>
#include <Arduino.h>


Communication::Communication(/* args */) {}

Communication::~Communication() {}

void Communication::setup() {
    Serial.begin(9600);
    Serial.println("== START ==");
    delay(10);
}

void Communication::update() {

}

void Communication::read() {

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