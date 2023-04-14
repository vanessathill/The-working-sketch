#include <Servo.h>

#define LEFT_PIN 9
#define RIGHT_PIN 10
#define VERT_PIN 11
#define CLAW_PIN 6

#define LEFT_SEL 2
#define RIGHT_SEL 4

#define JOY1_HOR A1
#define JOY1_VER A0

#define JOY2_HOR A3
#define JOY2_VER A4

#define MIN_PULSE 1000
#define MAX_PULSE 2000

Servo s_left;
Servo s_right;
Servo s_vert;
Servo s_claw;

int left_pulse = MIN_PULSE;
int right_pulse = MIN_PULSE;
int vert_pulse = MIN_PULSE;

int left_goal = MIN_PULSE;
int right_goal = MIN_PULSE;
int vert_goal = MIN_PULSE;

bool claw_open = true;

void setup() {
  Serial.begin(9600);

  pinMode(JOY1_HOR, INPUT);
  pinMode(JOY1_VER, INPUT);
  pinMode(JOY2_HOR, INPUT);
  pinMode(JOY2_VER, INPUT);

  pinMode(LEFT_SEL, INPUT_PULLUP);
  pinMode(RIGHT_SEL, INPUT_PULLUP);

  s_left.attach(LEFT_PIN, MIN_PULSE, MAX_PULSE);
  s_right.attach(RIGHT_PIN, MIN_PULSE, MAX_PULSE);
  s_vert.attach(VERT_PIN, MIN_PULSE, MAX_PULSE);
  s_claw.attach(CLAW_PIN);
  delay(5000);
}

void loop() {
  int y1 = map(analogRead(JOY1_VER), 0, 1023, -512, 511);
  int x1 = map(analogRead(JOY1_HOR), 0, 1023, -512, 511);
  int y2 = map(analogRead(JOY2_VER), 0, 1023, -512, 511);
  int x2 = map(analogRead(JOY2_HOR), 0, 1023, -512, 511);

  bool left_press = digitalRead(LEFT_SEL) == LOW;
  bool right_press = digitalRead(RIGHT_SEL) == LOW;

  // Update claw
  // if (left_press && !claw_open)
  //   claw_open = true;
  // else if (right_press && claw_open)
  //   claw_open = false;

  // // Update claw
  // if (claw_open) {
  //   s_claw.write(0);
  // } else {
  //   s_claw.write(180);
  // }

  // Update goals

  // Joystick 
  if (x1 < 99 && x1 > -100) {
    if (y1 < 99) {
      // Dead zone
      left_goal = MIN_PULSE;
      right_goal = MIN_PULSE;
    } else {
      left_goal = map(y1, 0, 511, MIN_PULSE, MAX_PULSE);
      right_goal = map(y1, 0, 511, MIN_PULSE, MAX_PULSE);
    }
  } else {
    if (x1 < 0) {
      right_goal = map(x1, -1, -512, MIN_PULSE, MAX_PULSE);
      left_goal = MIN_PULSE;
    } else {
      left_goal = map(x1, 0, 511, MIN_PULSE, MAX_PULSE);
      right_goal = MIN_PULSE;
    }
  }

  /// Joystick 2

  // top
  if (y2 > 50) {
    vert_goal = map(y2, 0, 511, MIN_PULSE, MAX_PULSE);
  }
  // bottom
  else {
    vert_goal = MIN_PULSE;
  }

  // Update motors themselves
  // Serial.print("XY: ");
  // Serial.print(x1);
  // Serial.print(" ");
  // Serial.print(y1);
  // Serial.print(" | ");

  // Serial.print("L: ");
  // Serial.print(left_goal);
  // Serial.print(" ");
  // Serial.print(left_pulse);
  // Serial.print(" | ");

  // Serial.print("R: ");
  // Serial.print(right_goal);
  // Serial.print(" ");
  // Serial.print(right_pulse);
  // Serial.print(" | ");

  // Serial.print("V: ");
  // Serial.print(vert_goal);
  // Serial.print(" ");
  // Serial.print(vert_pulse);
  // Serial.print("\n");


  if (left_goal > left_pulse) {
    left_pulse += 2;
    s_left.writeMicroseconds(left_pulse);
  } else if (left_goal < left_pulse) {
    left_pulse -= 2;
    s_left.writeMicroseconds(left_pulse);
  }

  if (right_goal > right_pulse) {
    right_pulse += 2;
    s_right.writeMicroseconds(right_pulse);
  } else if (right_goal < right_pulse) {
    right_pulse -= 2;
    s_right.writeMicroseconds(right_pulse);
  }

  if (vert_goal > vert_pulse) {
    vert_pulse += 2;
    s_vert.writeMicroseconds(vert_pulse);
  } else if (vert_goal < vert_pulse) {
    vert_pulse -= 2;
    s_vert.writeMicroseconds(vert_pulse);
  }

  delay(2);
}
