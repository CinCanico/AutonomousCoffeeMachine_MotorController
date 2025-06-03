/**
 * @file main.cpp
 * @author CinCanico
 * @brief Serial control middleware between Jetson Nano and "Mobile Autonomous Coffe Machine" electrical system.
 * @version 0.2
*/

//! Preprocessing

#include <Arduino.h>
#include <AsyncDelay.h>
#include <Encoder.h>
#include <Motor.h>
#include <string.h>

//* Interrupt Flag for reading encoders 
volatile bool interrupted = false;

//* Encoder Pins 
#define ENCODER_LA 2
#define ENCODER_LB 7
Encoder encoderL = Encoder(ENCODER_LA, ENCODER_LB);
// #define encRA 4
// #define encRB 5 
// Encoder encoderR = Encoder(encRA, encRB);

//* Motor Pins 
#define MOTOR_IN1L 4
#define MOTOR_IN2L 5
#define MOTOR_ENL 6
Motor motorL = Motor(MOTOR_IN1L, MOTOR_IN2L, MOTOR_ENL);
// #define IN2L 
// #define IN2R 


AsyncDelay delay_2s;
AsyncDelay delay_10ms;

//! Function Declarations 
//* Queued Async Processes
void move_forward();
void stop();
void move_backward();
bool set_process(void(*)());

void (*process_array[4])() = {move_forward, stop, move_backward, stop};
int process_number = 0;

//* Encoders
void sendSerialData_encoders(Encoder *);
void updateEncoder();

//! Arduino Code
void setup() {
  //* Begining Serial Communication over COM with Master (PC or Jetson)
  Serial.begin(9600);
  Serial.println("== START ==");

  //* Encoder Setup
  encoderL.setup();
  // ENCA pin of each encoder is placed on an interrupt pin 
  attachInterrupt(digitalPinToInterrupt(encoderL.GetInterruptPin()), updateEncoder, CHANGE);

  //* Motor Pinmodes 
  motorL.setup();

  //* Async Process Delay Start
  delay_2s.start(2000, AsyncDelay::units_t::MILLIS);
  // delay_10ms.start(10, AsyncDelay::units_t::MILLIS);
}


void loop() {
  if (set_process(process_array[process_number])) {
    process_number++;
    process_number = process_number % 4;
  }

  sendSerialData_encoders(&encoderL);
}

//! Function Definitions
void move_forward() {
  Serial.println("== forward == ");
  motorL.set_state(255, RotationDirection::CW);
}

void stop() {
  Serial.println("== stop == ");
  digitalWrite(MOTOR_ENL, 0);
  digitalWrite(MOTOR_IN1L, LOW);
  digitalWrite(MOTOR_IN2L, LOW);
}

void move_backward() {
  Serial.println("== backward == ");
  motorL.set_state(255, RotationDirection::CCW);
}

bool set_process(void(*foo)()) {
  if (!delay_2s.isExpired()) return false;

  foo();
  delay_2s.repeat();
  return true;
}

void sendSerialData_encoders(Encoder *encoder) {
  if (interrupted) {
    char message[25] = "$";
    char buffer[25];
    //* Encoder Pin State
    //strcat(message, itoa(encA, buffer, 10));
    //strcat(message, " ");
    //strcat(message, itoa(encB, buffer, 10));
    //strcat(message, ";");
    //* Motor Count
    strcat(message, itoa(encoder->GetAngle(), buffer, 10));
    strcat(message, ";");
    Serial.println(message);
    Serial.println("");
    interrupted = false;
  }
}

void updateEncoder() {
  // encA = (PIND & (1 << ENCODER_LA));
  // encB = (PIND & (1 << ENCODER_LB));
  encoderL.update();
  interrupted = true;
  // if (encA == encB) {
  //   //* Forward Movement / Add Position
  //   encoderLCount++;
  // }
  // else {
  //   //* Backward Movement / Subtract Position
  //   encoderLCount--;
  // }
}