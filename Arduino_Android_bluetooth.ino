#include <SoftwareSerial.h>
#include <DHT11.h>

DHT11 dht11(A0);
int Rx = 7;
int Tx = 8;
float temp;
int sound;
SoftwareSerial bt(Rx,Tx);
unsigned long previoustime = 0;
float currenthumi = 0;
float humilift = 0;
float previoushumi = 0;
int automation = 0;

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  unsigned long currenttime = (millis()/1000);
    if (currenttime - previoustime >= 60){ 
      dht11.read(currenthumi, temp);
      Serial.print("현재 습도 : ");
      Serial.println(currenthumi);
      Serial.print("현재 자동화 : ");
      if (automation == 1){    
        if (60<currenthumi){
          digitalWrite(6, HIGH); //환풍기 ON
        }
        else if(40<=currenthumi&&currenthumi<=60){
          digitalWrite(6, LOW); //환풍기 OFF
          digitalWrite(3, LOW); //가습기 OFF
        }
        else if (currenthumi<=40){
          digitalWrite(3, HIGH); //가습기 ON
        }
      }
      previoustime = currenttime;
    }
  
  if (bt.available()) {
    digitalWrite(13, HIGH); //부저 ON      
    int recive_value = (bt.parseInt());
    Serial.println(recive_value);=

    if(recive_value == 3){//전등 ON
      digitalWrite(10, HIGH);
    }
    else if(recive_value == 4){//전등 OFF
      digitalWrite(10, LOW);
    }
    else if(recive_value == 5){//가습기 relay module COM,ON 기준
      digitalWrite(3, HIGH);
    }
    else if(recive_value == 6){//가습기 relay module COM,ON 기준
      digitalWrite(3, LOW);
    }
    else if(recive_value == 7){//환풍기 ON
      digitalWrite(6, HIGH);
    }
    else if(recive_value == 8){//환풍 OFF
      digitalWrite(6, LOW);
    }
    else if(recive_value == 1){
      automation = 1; //자동화 ON
    }
    else if(recive_value == 9){
      automation = 0; //자동화 OFF
    }
    digitalWrite(13, LOW); //부저 OFF
  }
}
