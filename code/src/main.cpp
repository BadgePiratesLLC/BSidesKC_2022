#include <HardwareSerial.h>

const int LEDB = 3;
const int LEDS1 = 34;
const int LEDI = 4;
const int LEDD = 33;
const int LEDE = 5;
const int LEDS2 = 26;

const int LED0 = 6;
const int LED1 = 21;
const int LED2 = 14;
const int LED3 = 35;
const int LED4 = 10;
const int LED5 = 15;
const int LED6 = 36;
const int LED7 = 11;
const int LED8 = 16;
const int LED9 = 37;
const int LED10 = 12;
const int LED11 = 17;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");

  // Setup LEDS
  pinMode(LEDB, OUTPUT); 
  pinMode(LEDS1, OUTPUT); 
  pinMode(LEDI, OUTPUT); 
  pinMode(LEDD, OUTPUT); 
  pinMode(LEDE, OUTPUT); 
  // pinMode(LEDS2, OUTPUT); 
  pinMode(LED0, OUTPUT); 
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(LED3, OUTPUT); 
  pinMode(LED4, OUTPUT); 
  pinMode(LED5, OUTPUT); 
  pinMode(LED6, OUTPUT); 
  pinMode(LED7, OUTPUT); 
  pinMode(LED8, OUTPUT); 
  pinMode(LED9, OUTPUT); 
  pinMode(LED10, OUTPUT); 
  pinMode(LED11, OUTPUT); 

  digitalWrite(LEDB, LOW);   
  digitalWrite(LEDS1, LOW);   
  digitalWrite(LEDI, LOW);   
  digitalWrite(LEDD, LOW);   
  digitalWrite(LEDE, LOW);   
  // digitalWrite(LEDS2, LOW); 
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);
  digitalWrite(LED9, LOW);
  digitalWrite(LED10, LOW);
  digitalWrite(LED11, LOW);
  
}

void loop() {    
  digitalWrite(LEDB, HIGH);  
  delay(50);
  digitalWrite(LEDB, LOW);   
    
  digitalWrite(LEDS1, HIGH);  
  delay(50);
  digitalWrite(LEDS1, LOW);   
  
  digitalWrite(LEDI, HIGH);  
  delay(50);
  digitalWrite(LEDI, LOW);   

  digitalWrite(LEDD, HIGH);  
  delay(50);
  digitalWrite(LEDD, LOW);

  digitalWrite(LEDE, HIGH);  
  delay(50);
  digitalWrite(LEDE, LOW);   

  // digitalWrite(LEDS2, HIGH);  
  // delay(200);
  // digitalWrite(LEDS2, LOW);  

  digitalWrite(LED0, HIGH);  
  delay(50);
  digitalWrite(LED0, LOW);   


  digitalWrite(LED1, HIGH);  
  delay(50);
  digitalWrite(LED1, LOW);   

  digitalWrite(LED2, HIGH);  
  delay(50);
  digitalWrite(LED2, LOW);   

  digitalWrite(LED3, HIGH);  
  delay(50);
  digitalWrite(LED3, LOW);   

  digitalWrite(LED4, HIGH);  
  delay(50);
  digitalWrite(LED4, LOW);   

  digitalWrite(LED5, HIGH);  
  delay(50);
  digitalWrite(LED5, LOW);   


  digitalWrite(LED6, HIGH);  
  delay(50);
  digitalWrite(LED6, LOW);   

  digitalWrite(LED7, HIGH);  
  delay(50);
  digitalWrite(LED7, LOW);   

  digitalWrite(LED8, HIGH);  
  delay(50);
  digitalWrite(LED8, LOW);   

  digitalWrite(LED9, HIGH);  
  delay(50);
  digitalWrite(LED9, LOW);   

  digitalWrite(LED10, HIGH);  
  delay(50);
  digitalWrite(LED10, LOW);   

  digitalWrite(LED11, HIGH);  
  delay(50);
  digitalWrite(LED11, LOW);  
}
