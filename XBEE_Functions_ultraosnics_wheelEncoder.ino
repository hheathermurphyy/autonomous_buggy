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
char theChar; 

const int wheel_encoder = 2;
volatile int count;
float dist_travelled;
const float circumference = 0.19; // in metres
float timer;
float last_timer;

void forward ();
void turn_right();
void turn_left();
void junction_slow_down();
void stop_buggy();
void print_buggy_data();
void navigation_decision(bool right_sensor, bool left_sensor);


void setup() {
  
  Serial.begin(9600);
  delay( 1000 ); // Guard
  Serial.print("+++");
  delay( 1000 );
  Serial.println("ATID 3108, CH C, CN");
  delay( 1000 );
  while( Serial.read() != -1 );

  attachInterrupt( digitalPinToInterrupt(wheel_encoder), trigger, RISING);
  
  pinMode(left_eye, INPUT);
  pinMode(right_eye, INPUT);
  pinMode(forward_left, OUTPUT); 
  pinMode(backward_left, OUTPUT);
  pinMode(forward_right, OUTPUT);
  pinMode(backward_right, OUTPUT);
  pinMode (US_trig, OUTPUT);
  pinMode (US_echo, INPUT); 
  pinMode(wheel_encoder, INPUT_PULLUP);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void trigger(){
  count = count + 1;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
bool left_sensor = digitalRead( left_eye ); 
bool right_sensor = digitalRead( right_eye );
timer = millis();
  if (timer - last_timer > 3000){
          print_buggy_data();
  }
//------------------------------------------------------------------------------------------- 
        digitalWrite (US_trig, LOW);
        delayMicroseconds (2);
        digitalWrite (US_trig, HIGH);
        delayMicroseconds (10);
        digitalWrite (US_trig, LOW);

        duration = pulseIn (US_echo, HIGH);
        distance = duration/58;
//-------------------------------------------------------------------------------------------
         
  if( Serial.available() > 0 ){
      theChar = Serial.read();
  }
//-------------------------------------------------------------------------------------------
  if (theChar == 's'){
     stop_buggy();
     Serial.println ("Buggy has Stopped");
  }
//-------------------------------------------------------------------------------------------   
  else if (theChar == 'g'){     
        Serial.println ("Buggy has Started");
        navigation_decision (right_sensor,left_sensor);
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
if (distance <= 20){
    stop_buggy();
    Serial.println ("Obstacle detected - Buggy has stopped");
   }   

}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void forward (){
  float forward_timer = millis();
  analogWrite(forward_right, 140);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 140);
  digitalWrite(backward_right, LOW);

    if (forward_timer >= 2000){
      Serial.println ("Buggy Moving FORWARD");
      forward_timer = 0;
      }
      
 }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
void turn_right (){
  float right_timer = millis();
  analogWrite(forward_right, 50);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 160);
  digitalWrite(backward_right, LOW);

    if (right_timer >= 1500){
       Serial.println ("Buggy turning RIGHT");
       right_timer = 0;
       }
 }


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void turn_left(){  
  float left_timer = millis();   
  analogWrite(forward_right, 160);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 50);
  digitalWrite(backward_right, LOW);
  
   if (left_timer >= 1500) {
      Serial.println ("Buggy turning LEFT");
      left_timer = 0;
      }
 }
  
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void junction_slow_down(){   
  analogWrite(forward_right, 140);
  digitalWrite(backward_left, LOW);
  analogWrite(forward_left, 140);
  digitalWrite(backward_right, LOW);
  }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void stop_buggy(){   
  digitalWrite(forward_right, LOW );
  digitalWrite(backward_left, LOW);
  digitalWrite(forward_left, LOW);
  digitalWrite(backward_right, LOW);
  }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void print_buggy_data(){
  
  dist_travelled = (circumference / 5) * count ;
   Serial.print("Distance travelled: ");
   Serial.print( dist_travelled);
   Serial.println(" m ");

   Serial.print("Current Avg Speeg: ");
   Serial.print( dist_travelled / (timer/1000) );
   Serial.println(" m/s ");
   last_timer = millis();
   Serial.println("---------------------------");
  
  }

 
