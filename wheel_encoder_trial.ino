
const int wheel_encoder = 2;
volatile int count;
float dist_travelled;
const float circumference = 0.19; // in metres
float timer ;
float last_timer;

const int forward_left = 5;  
const int backward_left = 4;
const int forward_right = 6;
const int backward_right = 7;

void setup() {
  Serial.begin(9600);
  attachInterrupt( digitalPinToInterrupt(wheel_encoder), trigger, RISING);
  pinMode(wheel_encoder, INPUT_PULLUP);

  pinMode(forward_left, OUTPUT); 
  pinMode(backward_left, OUTPUT);
  pinMode(forward_right, OUTPUT);
  pinMode(backward_right, OUTPUT);


  
}

void trigger(){
  count = count + 1;
}

void loop() {
o
dist_travelled = (circumference / 5) * count ;
timer = millis();


  digitalWrite(forward_right, HIGH);
  digitalWrite(backward_left, LOW);
  digitalWrite(forward_left, HIGH);
  digitalWrite(backward_right, LOW);
  


if (timer - last_timer > 2000){
   Serial.print("Distance travelled: ");
   Serial.print( dist_travelled);
   Serial.println(" metres ");

   Serial.print("Current Avg Speeg: ");
   Serial.print( dist_travelled / (timer/1000) );
   Serial.println(" m/s ");
   
   last_timer = millis();
  
   
 }

}
//1 revolution = 5 spokes
//diameter = 6.1cm = 0.061m
//circumference = approx 0.19 
