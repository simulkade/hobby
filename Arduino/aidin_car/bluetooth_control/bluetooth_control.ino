#include<SoftwareSerial.h>

// LED code source: https://www.instructables.com/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/
// The rest of the code written by me by looking at different sources

const uint8_t lights[360]={
  0,   0,   0,   0,   0,   1,   1,   2, 
  2,   3,   4,   5,   6,   7,   8,   9, 
 11,  12,  13,  15,  17,  18,  20,  22, 
 24,  26,  28,  30,  32,  35,  37,  39, 
 42,  44,  47,  49,  52,  55,  58,  60, 
 63,  66,  69,  72,  75,  78,  81,  85, 
 88,  91,  94,  97, 101, 104, 107, 111, 
114, 117, 121, 124, 127, 131, 134, 137, 
141, 144, 147, 150, 154, 157, 160, 163, 
167, 170, 173, 176, 179, 182, 185, 188, 
191, 194, 197, 200, 202, 205, 208, 210, 
213, 215, 217, 220, 222, 224, 226, 229, 
231, 232, 234, 236, 238, 239, 241, 242, 
244, 245, 246, 248, 249, 250, 251, 251, 
252, 253, 253, 254, 254, 255, 255, 255, 
255, 255, 255, 255, 254, 254, 253, 253, 
252, 251, 251, 250, 249, 248, 246, 245, 
244, 242, 241, 239, 238, 236, 234, 232, 
231, 229, 226, 224, 222, 220, 217, 215, 
213, 210, 208, 205, 202, 200, 197, 194, 
191, 188, 185, 182, 179, 176, 173, 170, 
167, 163, 160, 157, 154, 150, 147, 144, 
141, 137, 134, 131, 127, 124, 121, 117, 
114, 111, 107, 104, 101,  97,  94,  91, 
 88,  85,  81,  78,  75,  72,  69,  66, 
 63,  60,  58,  55,  52,  49,  47,  44, 
 42,  39,  37,  35,  32,  30,  28,  26, 
 24,  22,  20,  18,  17,  15,  13,  12, 
 11,   9,   8,   7,   6,   5,   4,   3, 
  2,   2,   1,   1,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0};

const uint8_t HSVlights[61] = 
{0, 4, 8, 13, 17, 21, 25, 30, 34, 38, 42, 47, 51, 55, 59, 64, 68, 72, 76,
81, 85, 89, 93, 98, 102, 106, 110, 115, 119, 123, 127, 132, 136, 140, 144,
149, 153, 157, 161, 166, 170, 174, 178, 183, 187, 191, 195, 200, 204, 208,
212, 217, 221, 225, 229, 234, 238, 242, 246, 251, 255};

const uint8_t HSVpower[121] = 
{0, 2, 4, 6, 8, 11, 13, 15, 17, 19, 21, 23, 25, 28, 30, 32, 34, 36, 38, 40,
42, 45, 47, 49, 51, 53, 55, 57, 59, 62, 64, 66, 68, 70, 72, 74, 76, 79, 81, 
83, 85, 87, 89, 91, 93, 96, 98, 100, 102, 104, 106, 108, 110, 113, 115, 117, 
119, 121, 123, 125, 127, 130, 132, 134, 136, 138, 140, 142, 144, 147, 149, 
151, 153, 155, 157, 159, 161, 164, 166, 168, 170, 172, 174, 176, 178, 181, 
183, 185, 187, 189, 191, 193, 195, 198, 200, 202, 204, 206, 208, 210, 212, 
215, 217, 219, 221, 223, 225, 227, 229, 232, 234, 236, 238, 240, 242, 244, 
246, 249, 251, 253, 255};

// uint8_t outputPins[3] = {9, 10, 11}; // PWM pins
uint8_t R = 9; // red pin
uint8_t G = 10;
uint8_t B = 11;

// setRGBpoint (0, ...) for pins 3, 5, 6; setRGBpoint (1, ...) for pins 9, 10, 11.
// See array above


const int BI1 = 2;
const int BI2 = 3;
const int AI1 = 4;
const int AI2 = 5;
char input_cmd = 's';
int k = 0;
SoftwareSerial bt(6,7); // (Rx,Tx) 

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
  }
  else if (input_cmd == 'b') {
    motor_backward();
  }
  else if (input_cmd == 'r') {
    turn_right();
  }
  else if (input_cmd == 'l') {
    turn_left();
  }
  else if (input_cmd == 's') {
    motor_stop();
  }

  k++;
  if (k>=360){
    k=0;
  }
  sineLED(k);
  delay(25);
}

void backward_left(){
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
}

void forward_left(){
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
}

void backward_right(){
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
}

void forward_right(){
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

void setRGBpoint(uint8_t red, uint8_t green, uint8_t blue)
{
  // this code is for common anode LEDs. If you use common cathode ones,
  // remove the '255-' bits.
  analogWrite(R, 255-red);
  analogWrite(G, 255-green);
  analogWrite(B, 255-blue);
}

void sineLED(int angle)
{
  setRGBpoint(lights[(angle+120)%360], lights[angle],  lights[(angle+240)%360]);
}
