void setup() {
  Serial.begin(9600);
  pinMode(7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int cdsValue = analogRead(A1);
  Serial.print("cds =  ");
  Serial.println(cdsValue);
  if (cdsValue > 60) {
	digitalWrite(7, HIGH);
	Serial.println("MOTER ON (cds > 50)");
   }
  else {
	digitalWrite(7, LOW);
	Serial.println("LED OFF (cds < 50)");
  }
  delay(200); 
}
