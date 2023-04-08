#include <Servo.h>
Servo ESC1;     // create servo object to control the ESC
Servo ESC2;     // create servo object to control the ESC

int change_speed(int current_speed_m1, int new_speed, Servo ESC_number);
int motorpin_1 = 6;
int motorpin_2 = 5;
int stop_speed = 1000;
int current_speed_m1 = stop_speed;
int current_speed_m2 = stop_speed;
int default_speed = 1500;
void setup() {
  Serial.begin(9600);
  ESC1.attach(motorpin_1,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.attach(motorpin_2,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  delay(6000);
}

void loop() {
  char command = 0;
  
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'f') {
      current_speed_m1 = change_speed(current_speed_m1, default_speed, ESC1);
      current_speed_m2 = change_speed(current_speed_m2, default_speed, ESC2);

    } else if (command == 'l') {
      current_speed_m1 = change_speed(current_speed_m1, stop_speed, ESC1);
      current_speed_m2 = change_speed(current_speed_m2, default_speed, ESC2);

    } else if (command == 'r') {
      current_speed_m1 = change_speed(current_speed_m1, default_speed, ESC1);
      current_speed_m2 = change_speed(current_speed_m2, stop_speed, ESC2);
    
    } else if (command == 's') {
      current_speed_m1 = change_speed(current_speed_m1, stop_speed, ESC1);
      current_speed_m2 = change_speed(current_speed_m2, stop_speed, ESC2);
    }
  }

  Serial.println(ESC1.read());

}

int change_speed(int current_speed, int new_speed, Servo ESC_number) {

  if (current_speed < new_speed) {
    for (int i = current_speed; i < new_speed; i ++) {
      ESC_number.writeMicroseconds(i);
      delay(10);
    }

  } else {
    for (int i = current_speed; i > new_speed; i --) {
      ESC_number.writeMicroseconds(i);
      delay(10);
    }
  }

  return new_speed;
}
