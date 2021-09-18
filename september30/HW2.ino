
const int in1Pin = 7;
const int in2Pin = 6;
const int in3Pin = 5;
const int in4Pin = 4;


#include <Servo.h>

Servo myservo;
int pos = 0;   

void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  myservo.attach(9);

}

void loop() {

    //make the robot go straight
    digitalWrite(in1Pin, LOW);
    analogWrite(in2Pin, 100);
    analogWrite(in3Pin, 100);
    digitalWrite(in4Pin, LOW);

    delay(1000);

    //make the robot turn left and right
    digitalWrite(in1Pin, LOW);
    analogWrite(in2Pin, 50);
    analogWrite(in3Pin, 100);
    digitalWrite(in4Pin, LOW);

    delay(2000);

    digitalWrite(in1Pin, LOW);
    analogWrite(in2Pin, 100);
    analogWrite(in3Pin, 50);
    digitalWrite(in4Pin, LOW);

    delay(2000);
    
    //make the robot "say hello"
    for (pos = 90; pos <= 180; pos += 1) { 
        myservo.write(pos);            
        delay(15);                     
  }
    for (pos = 180; pos >= 90; pos -= 1) { 
        myservo.write(pos);             
        delay(15);                       
  }
  

}
