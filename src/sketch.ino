// -*- c -*-
// SwordWave Arduino sketch
//
// Copyright (c) 2014 Dave Sieh
// 
// See LICENSE for details.
//
#include <Servo.h>
#include <VCNL4000.h>
#include <pspc_support.h>

#define SERVO_PIN 9

#define AT_REST 0
#define ATTACK 90

VCNL4000 proximitySensor;
Servo servo;

boolean state = false;

void setup() {
  Serial.begin(9600);

  proximitySensor.begin();

  servo.attach(SERVO_PIN);
  servo.write(AT_REST);

  Serial.println(P("Ready"));
}

void loop() {
  uint16_t distance = proximitySensor.readProximity();

  if (distance > 2150) {
    if (!state) {
      Serial.println(P("InRange"));
      state = true;
      servo.write(ATTACK);
    }
  } else {
    if (state) {
      Serial.println(P("OutOfRange"));
      state = false;
      servo.write(AT_REST);
    }
  }

  delay(100);
}
