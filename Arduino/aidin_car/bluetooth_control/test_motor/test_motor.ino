const int BI1 = 2;
const int BI2 = 3;
const int AI1 = 4;
const int AI2 = 5;
char state = '0';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  motor_stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  motor_forward();
  delay(1000);
  motor_backward();
  delay(1000);
  turn_right();
  delay(1000);
  turn_left();
  delay(1000);
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
