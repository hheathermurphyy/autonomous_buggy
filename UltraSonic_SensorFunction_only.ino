
#define black  HIGH
#define white  LOW

const int left_eye = A3;
const int right_eye = A4;

const int forward_left = 5;  
const int backward_left = 4;
const int forward_right = 6;
const int backward_right = 7;

const int US_trig = 9;
const int US_echo = 8;
double distance = 0;
double duration;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(forward_left, OUTPUT); 
  pinMode(backward_left, OUTPUT);
  pinMode(forward_right, OUTPUT);
  pinMode(backward_right, OUTPUT);
  
  pinMode (US_trig, OUTPUT);
  pinMode (US_echo, INPUT); 
  
digitalWrite(forward_right, HIGH);
digitalWrite(backward_left, LOW);
digitalWrite(forward_left, HIGH);
digitalWrite(backward_right, LOW);
 
}

void loop(){
  
digitalWrite(forward_right, HIGH);
digitalWrite(backward_left, LOW);
digitalWrite(forward_left, HIGH);
digitalWrite(backward_right, LOW);

unsigned long timer = millis();  

generate_ultrasonic();
Serial.println(distance);

if (distance <= 20){
  stop_buggy();
}
if (distance > 20){
  stop_buggy();
}
 
}




//---------------------------------------------------------------------------------------------------------------------------------------------
/*void check_distance(double distance) {
  
if (distance <= 20){
  Serial.println(distance);
  stop_buggy();
  
  }
}*/ 
//----------------------------------------------------------------------------------------------------------------------------------------------
void stop_buggy() {
  digitalWrite(forward_right, LOW);
  digitalWrite(backward_left, LOW);
  digitalWrite(forward_left, LOW);
  digitalWrite(backward_right, LOW);
}
//-------------------------------------------------------------------------------------------------------------------------
void forward_buggy() {
  digitalWrite(forward_right, HIGH);
  digitalWrite(backward_left, LOW);
  digitalWrite(forward_left, HIGH);
  digitalWrite(backward_right, LOW);
}
//----------------------------------------------------------------------------------------------------------------------------------------------
void generate_ultrasonic(){
 digitalWrite (US_trig, LOW);
 delayMicroseconds (2);
 digitalWrite (US_trig, HIGH);
 delayMicroseconds (10);
 digitalWrite (US_trig, LOW);

duration = pulseIn (US_echo, HIGH);
distance = duration/58;

}
