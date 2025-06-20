/**
 * @file main.cpp
 * @author CinCanico
 * @brief Serial control middleware between Jetson Nano and "Mobile Autonomous Coffe Machine" electrical system.
 * @version 0.2
*/

//! Preprocessing

#include <Arduino.h>
#include <AsyncDelay.h>
#include <string.h>

#include <Encoder.h>
#include <Motor.h>
#include <Communication.h>

//* Interrupt Flag for reading encoders 
volatile bool interrupted = false;

//* Encoder Pins 
#define ENCODER_LA 2 // Interrupt
#define ENCODER_LB 4
#define ENCODER_RA 3 // Interrupt
#define ENCODER_RB 5 
Encoder encoderL = Encoder(ENCODER_LA, ENCODER_LB);
Encoder encoderR = Encoder(ENCODER_RA, ENCODER_RB);

//* Motor Pins 
#define MOTOR_IN1L 8
#define MOTOR_IN2L 7
#define MOTOR_ENL 6 // PMW
#define MOTOR_IN1R 13
#define MOTOR_IN2R 12
#define MOTOR_ENR 11// PMW
Motor motorL = Motor(MOTOR_IN1L, MOTOR_IN2L, MOTOR_ENL);
Motor motorR = Motor(MOTOR_IN1R, MOTOR_IN2R, MOTOR_ENR);


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
void interrupt_system();

//* Communication Interface
Communication commIntrface = Communication();

//! Arduino Code
void setup() {
  //* Begining Serial Communication with Master (RaspberryPi)
  commIntrface.setup();

  //* Encoder Setup
  encoderL.setup();
  encoderR.setup();
  // ENCA pin of each encoder is placed on an interrupt pin 
  attachInterrupt(digitalPinToInterrupt(encoderL.GetInterruptPin()), interrupt_system, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderR.GetInterruptPin()), interrupt_system, CHANGE);

  //* Motor Pinmodes 
  motorL.setup();
  motorR.setup();

  //* Async Process Delay Start
  delay_2s.start(2000, AsyncDelay::units_t::MILLIS);
  // delay_10ms.start(10, AsyncDelay::units_t::MILLIS);
}


void loop() {
  if (set_process(process_array[process_number])) {
    process_number++;
    process_number = process_number % 4;
  }
  if (!interrupted) {
    commIntrface.read();
  }
}

//! Function Definitions
void move_forward() {
  Serial.println("== forward == ");
  motorL.set_state(255, RotationDirection::CW);
  motorR.set_state(255, RotationDirection::CW);
}

void stop() {
  Serial.println("== stop == ");
  digitalWrite(MOTOR_ENL, 0);
  digitalWrite(MOTOR_IN1L, LOW);
  digitalWrite(MOTOR_IN2L, LOW);
  digitalWrite(MOTOR_ENR, 0);
  digitalWrite(MOTOR_IN1R, LOW);
  digitalWrite(MOTOR_IN2R, LOW);
}

void move_backward() {
  Serial.println("== backward == ");
  motorL.set_state(255, RotationDirection::CCW);
  motorR.set_state(255, RotationDirection::CCW);
}

bool set_process(void(*foo)()) {
  if (!delay_2s.isExpired()) return false;

  foo();
  delay_2s.repeat();
  return true;
}


void interrupt_system() {
  encoderL.update();
  encoderR.update();
  commIntrface.update();
  // commIntrface.plotData(encoderL.GetAngle());
  interrupted = true;
}