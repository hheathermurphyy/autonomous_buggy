//true = 1 = HIGH  = BLACK
//false = 0 = LOW = WHITE = hand_under , green light is on 

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
float distance, duration;
unsigned long timer;  
void forward ();
void turn_right();
void turn_left();
void junction_slow_down();
void stop_buggy();

void setup() {
  
  Serial.begin(9600);

  pinMode(left_eye, INPUT);
  pinMode(right_eye, INPUT);
  pinMode(forward_left, OUTPUT); 
  pinMode(backward_left, OUTPUT);
  pinMode(forward_right, OUTPUT);
  pinMode(backward_right, OUTPUT);
  pinMode (US_trig, OUTPUT);
  pinMode (US_echo, INPUT); 

  analogWrite(forward_right, 170);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 170);
  digitalWrite(backward_right, LOW);
  delay (3000);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:


bool left_sensor = digitalRead( left_eye ); 
bool right_sensor = digitalRead( right_eye );

digitalWrite (US_trig, LOW);
delayMicroseconds (2);
digitalWrite (US_trig, HIGH);
delayMicroseconds (10);
digitalWrite (US_trig, LOW);

 duration = pulseIn (US_echo, HIGH);
 distance = duration/58;
 Serial.println(distance);

 if (distance <= 10){
  stop_buggy();
  delay (1000);
}

else {
  navigation_decision(right_sensor,left_sensor);
  } 


}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void navigation_decision(bool right_sensor, bool left_sensor){

if(right_sensor==black && left_sensor==black){
  forward();
  }
if(left_sensor==black && right_sensor==white){
  turn_right();
}
if(left_sensor==white && right_sensor==black){
  turn_left();
}
if(left_sensor==white && right_sensor==white){
  junction_slow_down();
}

}

void forward (){
  analogWrite(forward_right, 170);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 170);
  digitalWrite(backward_right, LOW);
  }

 
void turn_right (){
  analogWrite(forward_right, 64);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 190);
  digitalWrite(backward_right, LOW);
  }



void turn_left(){     
  analogWrite(forward_right, 190);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 64);
  digitalWrite(backward_right, LOW);
  }
  
 
void junction_slow_down(){   
  analogWrite(forward_right, 75);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 75);
  digitalWrite(backward_right, LOW);
  }

void stop_buggy(){   
  digitalWrite(forward_right, LOW );
  digitalWrite(backward_left, LOW);
  digitalWrite(forward_left, LOW);
  digitalWrite(backward_right, LOW);
  }
  
