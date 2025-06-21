/**
 * @file main.cpp
 * @author CinCanico
 * @brief Serial control middleware between RaspberryPi and "Mobile Autonomous Coffe Machine" electrical system.
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
#define MOTOR_IN1L 9
#define MOTOR_IN2L 8
#define MOTOR_ENL 10 // PMW
#define MOTOR_IN1R 13
#define MOTOR_IN2R 12
#define MOTOR_ENR 11// PMW
Motor motorL = Motor(MOTOR_IN1L, MOTOR_IN2L, MOTOR_ENL);
Motor motorR = Motor(MOTOR_IN1R, MOTOR_IN2R, MOTOR_ENR);


AsyncDelay delay_2s;
AsyncDelay delay_10ms;

//! Function Declarations 
//* Queued Async Processes
void move_forwardright();
void move_forwardleft();
void move_forward();
void move_forwardright();
void move_left();
void move_stop();
void move_right();
void move_backwardleft();
void move_backward();
void move_backwardright();


//* Encoders
void sendSerialData_encoders(Encoder *);
void interrupt_system();

//* Communication Interface
Communication commIntrface = Communication();
DirectionCommands lastCommand = COM_Stop;

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
  if (interrupted) return;

  commIntrface.update();
  DirectionCommands comNow = commIntrface.GetCurrentCommand();

  if (comNow == lastCommand) return;

  switch (comNow) {
  case COM_ForwardLeft:
    move_forwardleft();
    break;
  case COM_ForwardRight:
    move_forwardright();
    break;
  case COM_Forward:
    move_forward();
    break;
  case COM_BackwardLeft:
    move_backwardleft();
    break;
  case COM_BackwardRight:
    move_backwardright();
    break;
  case COM_Backward:
    move_backward();
    break;
  case COM_Left:
    move_left();
    break;
  case COM_Right:
    move_right();
    break;
  case COM_Stop:
    move_stop();
    break;
  default:
    break;
  }
  lastCommand = comNow;
}

void interrupt_system() {
  encoderL.update();
  encoderR.update();
  // commIntrface.plotData(encoderL.GetAngle());
  interrupted = true;
}

//! Function Definitions

//* Forward
void move_forwardleft() {
  Serial.println("== forward left == ");
  motorL.set_state(150, MovementDirection::MOVE_Forward, Side::SIDE_Left);
  motorR.set_state(255, MovementDirection::MOVE_Forward, Side::SIDE_Right);
}


void move_forward() {
  Serial.println("== forward == ");
  motorL.set_state(255, RotationDirection::ROTATION_CW);
  motorR.set_state(255, RotationDirection::ROTATION_CW);
}

void move_forwardright() {
  Serial.println("== forward right == ");
  motorL.set_state(255, MovementDirection::MOVE_Forward, Side::SIDE_Left);
  motorR.set_state(150, MovementDirection::MOVE_Forward, Side::SIDE_Right);
}

//* In Place
void move_left() {
  Serial.println("== full left == ");
  motorL.stop();
  motorR.set_state(255, MOVE_Forward, SIDE_Right);
}
void move_stop() {
  Serial.println("== stop == ");
  motorL.stop();
  motorR.stop();
}
void move_right() {
  Serial.println("== full right == ");
  motorL.set_state(255, MOVE_Forward, SIDE_Right);
  motorR.stop();
}

//* Backward
void move_backwardleft() {
  Serial.println("== backward left== ");
  motorL.set_state(150, RotationDirection::ROTATION_CCW);
  motorR.set_state(255, RotationDirection::ROTATION_CCW);
}

void move_backward() {
  Serial.println("== backward == ");
  motorL.set_state(255, RotationDirection::ROTATION_CCW);
  motorR.set_state(255, RotationDirection::ROTATION_CCW);
}
void move_backwardright() {
  Serial.println("== backward right== ");
  motorL.set_state(255, RotationDirection::ROTATION_CCW);
  motorR.set_state(150, RotationDirection::ROTATION_CCW);
}



