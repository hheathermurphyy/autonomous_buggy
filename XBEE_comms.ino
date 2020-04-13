void setup() {
  
Serial.begin(9600);
  delay( 1000 ); // Guard
  Serial.print("+++");
  delay( 1000 );
  Serial.println("ATID 3108, CH C, CN");
  delay( 1000 );
  while( Serial.read() != -1 );

 

}

void loop() {
  // put your main code here, to run repeatedly:

}
