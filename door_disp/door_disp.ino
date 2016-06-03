int A_RIGHT_OPEN = 3; 
int A_RIGHT_CLOSE = 4; 
int A_LEFT_OPEN = 5; 
int A_LEFT_CLOSE = 6; 

int B_RIGHT_OPEN = A1; 
int B_RIGHT_CLOSE = A2; 
int B_LEFT_OPEN = A3; 
int B_LEFT_CLOSE = A4; 

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    switch(inChar) {
      case '3':
      digitalWrite(A_LEFT_OPEN,HIGH); 
      digitalWrite(A_LEFT_CLOSE,LOW); 
      Serial.print("A");
      break;
      case '4':
      digitalWrite(A_LEFT_OPEN,LOW); 
      digitalWrite(A_LEFT_CLOSE,HIGH); 
      Serial.print("B");
      break;
      case '5':
      digitalWrite(A_RIGHT_OPEN,HIGH); 
      digitalWrite(A_RIGHT_CLOSE,LOW); 
      Serial.print("C");
      break;
      case '6':
      digitalWrite(A_RIGHT_OPEN,LOW); 
      digitalWrite(A_RIGHT_CLOSE,HIGH); 
      Serial.print("D");
      break;
      case 'A':
      digitalWrite(B_LEFT_OPEN,HIGH); 
      digitalWrite(B_LEFT_CLOSE,LOW); 
      break;
      case 'B':
      digitalWrite(B_LEFT_OPEN,LOW); 
      digitalWrite(B_LEFT_CLOSE,HIGH); 
      break;
      case 'C':
      digitalWrite(B_RIGHT_OPEN,HIGH); 
      digitalWrite(B_RIGHT_CLOSE,LOW); 
      break;
      case 'D':
      digitalWrite(B_RIGHT_OPEN,LOW); 
      digitalWrite(B_RIGHT_CLOSE,HIGH);             
      break;
      default:
      break;    
    } 
  }
} 

void setup() {
   Serial.begin(9600);
   pinMode(A_LEFT_OPEN,OUTPUT);
   pinMode(A_RIGHT_OPEN,OUTPUT);
   pinMode(A_LEFT_CLOSE,OUTPUT);
   pinMode(A_RIGHT_CLOSE,OUTPUT);
   pinMode(B_LEFT_OPEN,OUTPUT);
   pinMode(B_RIGHT_OPEN,OUTPUT);
   pinMode(B_LEFT_CLOSE,OUTPUT);
   pinMode(B_RIGHT_CLOSE,OUTPUT);
}

void loop() {
}



