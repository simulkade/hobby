const int BI1 = 5;
const int BI2 = 6;
const int AI1 = 10;
const int AI2 = 9;
const unsigned int TRIG_PIN=7;
const unsigned int ECHO_PIN=8;
const unsigned int BAUD_RATE=9600;
byte speed = 255; //This can be between 0 to 255 to control the speed
const int move_delay = 2000; //mili second

void setup() {
  // put your setup code here, to run once:
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
//  pinMode(ECHO_PIN, INPUT);
//  Serial.begin(BAUD_RATE);

}

float get_distance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
  float distance= duration/29/2;
  return distance;
}

void forward_left(){
  analogWrite(AI1, speed);
  analogWrite(AI2, 0);
}

void backward_left(){
  analogWrite(AI1, 0);
  analogWrite(AI2, speed);
}

void forward_right(){
  analogWrite(BI1, 0);
  analogWrite(BI2, speed);
}

void backward_right(){
  analogWrite(BI1, speed);
  analogWrite(BI2, 0);
}

void motor_stop(){
  analogWrite(AI1, 0);
  analogWrite(AI2, 0);
  analogWrite(BI1, 0);
  analogWrite(BI2, 0);
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





void loop() {
//  int distance_old = get_distance();
//  if(distance_old>10){
//    motor_forward();
//  }
//  delay(500);
//  if(distance_old<10){
//    motor_backward();
//  }
//  delay(500);
  int turn_time = 700; //mili second
  int move_time = 100; //mili second
  float danger_distance = 10.0; // cm

  // look at the front and measure distance
  //motor_stop();
  float distance_front = get_distance();

  if(distance_front<danger_distance){
    //turn left and measure distance
    turn_left();
    delay(turn_time);
    motor_stop();
    float distance_left = get_distance();
    //turn right and measure distance
    turn_right();
    delay(2*turn_time);
    motor_stop();
    float distance_right = get_distance();
    //turn back to face the front
    turn_left();
    delay(turn_time);
    motor_stop();

    // choose where to go
    if((distance_right>distance_front) && (distance_right>danger_distance) && (distance_right>distance_left)){
      turn_right();
      delay(turn_time);
      motor_forward();
      delay(move_time);
      motor_stop();
    }
    else if((distance_left>distance_front) && (distance_left>danger_distance) && (distance_right<distance_left)){
      turn_left();
      delay(turn_time);
      motor_forward();
      delay(move_time);
      motor_stop();
    }
    else{
      motor_backward();
      delay(move_time);
      motor_stop();
    }
  }
  else{
    motor_forward();
    delay(move_time);
    motor_stop();
  }

  if(distance_front == 0){
      motor_backward();
      delay(move_time);
      motor_stop();
    }
  


  
//  if(distance_old<20){
//    turn_left();
//    }
//  else{
//    motor_forward();
//  }      
//  delay(move_delay);
//  int distance = get_distance();
//  if(distance-distance_old>=0){
//    motor_forward();
//    }
//  else{
//    turn_right();
//  }
//  
//  delay(move_delay);

}
