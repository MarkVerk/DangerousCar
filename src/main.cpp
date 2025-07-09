#include <Arduino.h>
#include <SoftwareSerial.h>

struct Motor {
  int pinA, pinB;
};


Motor LB = {D2, D3};
Motor RB = {D4, D5};
Motor LF = {D6, D7};
Motor RF = {D8, D9};


SoftwareSerial bt(D10, D11);



uint64_t lastCmd = 0;
char cmd = 0;


void initMotor(Motor& motor) {
  pinMode(motor.pinA, OUTPUT);
  pinMode(motor.pinB, OUTPUT);
}

void mcontrol(Motor& motor, int val) {
  if (val == 0) {
    digitalWrite(motor.pinA, 0);
    digitalWrite(motor.pinB, 0);
  }
  else if (val == 1) {
    digitalWrite(motor.pinA, 1);
    digitalWrite(motor.pinB, 0);
  }
  else if (val == -1) {
    digitalWrite(motor.pinA, 0);
    digitalWrite(motor.pinB, 1);
  }
}


void setup() {
  Serial.begin(115200);
  bt.begin(9600);
  initMotor(LB);
  initMotor(RB);
  initMotor(LF);
  initMotor(RF);
}


void loop() {
  if (bt.available() > 0) {
    cmd = bt.read();
    lastCmd = millis();
  }
  if (millis() - lastCmd >= 500) {
    mcontrol(LB, 0);
    mcontrol(RB, 0);
    mcontrol(LF, 0);
    mcontrol(RF, 0);
  }
  else {
    switch (cmd) {
      case 'f':
        mcontrol(LB, 1);
        mcontrol(RB, 1);
        mcontrol(LF, 1);
        mcontrol(RF, 1);
        break;
      case 'b':
        mcontrol(LB, -1);
        mcontrol(RB, -1);
        mcontrol(LF, -1);
        mcontrol(RF, -1);
        break;
      case 'l':
        mcontrol(LB, -1);
        mcontrol(RB, 1);
        mcontrol(LF, -1);
        mcontrol(RF, 1);
        break;
      case 'r':
        mcontrol(LB, 1);
        mcontrol(RB, -1);
        mcontrol(LF, 1);
        mcontrol(RF, -1);
        break;
      case 'd': // that dangerous part
        mcontrol(LB, 1);
        mcontrol(RB, 1);
        mcontrol(LF, 1);
        mcontrol(RF, 1);
        break;
    }
  }
}