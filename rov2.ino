#include <Servo.h>

#define LEFT_PIN 9
#define RIGHT_PIN 10
#define VERT_PIN 11

// Analog input pins
#define JOY1_HOR A1
#define JOY1_VER A0

#define JOY2_HOR A3
#define JOY2_VER A4

#define MIN_PULSE 1000
#define MAX_PULSE 2000

Servo s_left;
Servo s_right;
Servo s_vert;

int left_pulse = MIN_PULSE;
int right_pulse = MIN_PULSE;
int vert_pulse = MIN_PULSE;

// Primitive controller
int left_goal = MIN_PULSE;
int right_goal = MIN_PULSE;
int vert_goal = MIN_PULSE;

void setup() {
  pinMode(JOY1_HOR, INPUT);
  pinMode(JOY1_VER, INPUT);
  pinMode(JOY2_HOR, INPUT);
  pinMode(JOY2_VER, INPUT);

  s_left.attach(LEFT_PIN, MIN_PULSE, MAX_PULSE);
  s_right.attach(RIGHT_PIN, MIN_PULSE, MAX_PULSE);
  s_vert.attach(VERT_PIN, MIN_PULSE, MAX_PULSE);
  delay(5000);
}

void loop() {
  int y1 = analogRead(JOY1_VER);
  int x1 = analogRead(JOY1_HOR);
  int y2 = analogRead(JOY2_VER);
  int x2 = analogRead(JOY2_HOR);

  // Update goals

  /// Joystick 1
  // bottom
  if (y1 < 512) {
    // pass
  }
  //top
  else {
    left_goal = map(y1, 512, 1023, MIN_PULSE, MAX_PULSE);
    right_goal = map(y1, 512, 1023, MIN_PULSE, MAX_PULSE);
  }

  // if the vert is 0, then both left and right goal will be MIN_PULSE
  // depending on the horz, left and right have their scale overridden accordingly

  // right
  if (x1 < 512) {
    left_goal = map(x1, 0, 511, MIN_PULSE, MAX_PULSE);
  }
  // left
  else {
    right_goal = map(x1, 512, 1023, MIN_PULSE, MAX_PULSE);
  }

  /// Joystick 2

  // bottom
  if (y1 < 512) {
    // pass
  }
  //top
  else {
    vert_goal = map(y2, 512, 1023, MIN_PULSE, MAX_PULSE);
  }

  // Update motors themselves
  if (left_goal > left_pulse < 0) {
    s_left.writeMicroseconds(++left_pulse);
  } else if (left_goal < left_pulse) {
    s_left.writeMicroseconds(--left_pulse);
  }

  if (right_goal > right_pulse < 0) {
    s_right.writeMicroseconds(++right_pulse);
  } else if (right_goal < right_pulse) {
    s_right.writeMicroseconds(--right_pulse);
  }

  if (vert_goal > vert_pulse < 0) {
    s_vert.writeMicroseconds(++vert_pulse);
  } else if (vert_goal < vert_pulse) {
    s_vert.writeMicroseconds(--vert_pulse);
  }

  delay(10);
}
