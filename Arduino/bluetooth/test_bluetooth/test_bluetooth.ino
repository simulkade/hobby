const int red = 9;
const int green = 10;
const int blue = 11;
int state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  LED_off();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
  }
  if (state == '0') {
    LED_off();
    digitalWrite(red, LOW); // Turn LED OFF
    Serial.println("LED: red"); // Send back, to the phone, the String "LED: ON"
    state = 0;
 }
 else if (state == '1') {
   LED_off();
   digitalWrite(blue, LOW);
   Serial.println("LED: blue");
   state = 0;
 } 
}

void LED_off(){
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
}
