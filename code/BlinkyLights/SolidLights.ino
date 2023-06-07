void setup() {
  // put your setup code here, to run once:
pinMode(3,OUTPUT);
pinMode(34,OUTPUT);
pinMode(4,OUTPUT);
pinMode(33,OUTPUT);
pinMode(5,OUTPUT);
pinMode(26,OUTPUT);
pinMode(6,OUTPUT);
pinMode(21,OUTPUT);
pinMode(14,OUTPUT);
pinMode(35,OUTPUT);
pinMode(10,OUTPUT);
pinMode(15,OUTPUT);
pinMode(36,OUTPUT);
pinMode(11,OUTPUT);
pinMode(16,OUTPUT);
pinMode(37,OUTPUT);
pinMode(12,OUTPUT);
pinMode(17,OUTPUT);

Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(3,HIGH);
digitalWrite(34,HIGH);
digitalWrite(4,HIGH);
digitalWrite(33,HIGH);
digitalWrite(5,HIGH);
digitalWrite(26,HIGH);
digitalWrite(6,HIGH);
digitalWrite(21,HIGH);
digitalWrite(14,HIGH);
digitalWrite(35,HIGH);
digitalWrite(10,HIGH);
digitalWrite(15,HIGH);
digitalWrite(36,HIGH);
digitalWrite(11,HIGH);
digitalWrite(16,HIGH);
digitalWrite(37,HIGH);
digitalWrite(12,HIGH);
digitalWrite(17,HIGH);

Serial.println ("Alive");
}
