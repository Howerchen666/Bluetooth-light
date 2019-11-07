//--------------------importing module----------------------------
#include <SoftwareSerial.h>

//--------------------initialize variable-------------------------
int state = 5;
int ledStaysHighFor = 700;  
int ledStaysLowFor = 1000;  
int highSince = 0;  
int lowSince = 0;  
int ledStatus = LOW; 
unsigned long ledPeriode = 1000;
int command;

//port config
const int led = 5;
const int microphone = 4;

SoftwareSerial Bluetooth(7, 8);    //set Buletooth Module TXD to pin 7 and RXD on pin 8

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(led, OUTPUT);
  pinMode (microphone, INPUT);
}

void loop() {  
  if (state == 1){
   // Reciving command 1 will trigger led state 1(flighting up simultamiusly)
   digitalWrite(led, LOW);
    }
    
    if (state == 2){
     int now = millis();
      if(ledStatus == HIGH && now - lowSince >= ledStaysLowFor)  
      {  
           highSince = now;
           ledStatus = LOW;
           digitalWrite(led, HIGH);
      }  
      else if(ledStatus == LOW && now - highSince >= ledStaysHighFor)
      {  
           lowSince = now;  
           ledStatus = HIGH;  
           digitalWrite(led, LOW);
      }
    }
    
    if (state == 3){
    //Reciving command 3 will triger 
    unsigned long now = millis();  
    int val = 128 + 127 * cos(2 * PI / ledPeriode * now);  
    analogWrite(led, val);
    }

    if (state == 4){
        int statusSensor = digitalRead (microphone);
  
        if (statusSensor == 1)
        {
        digitalWrite(led, LOW);
        }
        else
        {
         digitalWrite(led, HIGH);
        }
        }
    
    if (state == 5){
      digitalWrite(led, HIGH);
    }


   if (Bluetooth.available()) {
    command = Bluetooth.read();
    if (command == '1'){
    state = 1;
    }
    if (command == '2'){
    state = 2;
    }
    if (command == '3'){
    state = 3;
    }
    if (command == '4'){
    state = 4;
    }
    if (command == '5'){
    state = 5;
    }
  }
}
