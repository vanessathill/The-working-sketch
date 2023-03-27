#include <Servo.h>
Servo ESC1;     // create servo object to control the ESC
Servo ESC2;     // create servo object to control the ESC

void setup() {
  Serial.begin(9600);
  ESC1.attach(6,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.attach(5,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  delay(6000);
}

void loop() {
   for (int i = 1000; i < 1050; i++) {
    ESC1.writeMicroseconds(i);
    ESC2.writeMicroseconds(i);
    /*
    if (i> 1250)  {
      delay(1000); // halt motor for 1 second
      i -= 1;
    }
    */    
    delay(10);
    Serial.println(i);
  }


  // Stalling the loop by entering an infinite while loop
  int check = 0;
  // During this stall the speed is 0
  ESC1.writeMicroseconds(0);
  ESC2.writeMicroseconds(0);
  while (check == 0) {
  
  }
}
