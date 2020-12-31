#include<SoftwareSerial.h>

const int BI1 = 2;
const int BI2 = 3;
const int AI1 = 4;
const int AI2 = 5;
char input_cmd = 's';
SoftwareSerial bt(6,7); /* (Rx,Tx) */ 

void setup() {
  // put your setup code here, to run once:
  bt.begin(9600);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  motor_stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(bt.available() > 0){
    input_cmd = bt.read();
  }
  if (input_cmd == 'f') {
    motor_forward();
//      Serial.println("going forward");
  }
  else if (input_cmd == 'b') {
    motor_backward();
//      Serial.println("going backward");
  }
  else if (input_cmd == 'r') {
    turn_right();
//      Serial.println("turning right");
  }
  else if (input_cmd == 'l') {
    turn_left();
//      Serial.println("turning left");
  }
  else if (input_cmd == 's') {
    motor_stop();
//      Serial.println("turning left");
  }
  delay(25);
}

void forward_left(){
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
}

void backward_left(){
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
}

void forward_right(){
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
}

void backward_right(){
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
}

void motor_stop(){
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, LOW);
}

void motor_forward(){
  forward_right();
  forward_left();
}

void motor_backward(){
  backward_right();
  backward_left();
}

void turn_left(){
  backward_left();
  forward_right();
}

void turn_right(){
  backward_right();
  forward_left();
}
