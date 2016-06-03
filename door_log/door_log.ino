#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 rtc;
//written by Hanjun Kim
volatile unsigned long LastInterrupt[] = {0,0} ;
volatile int ToiletState[] = {0,0} ;
volatile unsigned long InterruptTime0 = 0;
volatile unsigned long InterruptTime1 = 0;

unsigned long block = 50; // the NOinterrupts period
int PWR = 7;
int LEFT_LED = 5; // Interrupt 0
int RIGHT_LED = 6; // Interrupt 1
volatile uint32_t initTime;
volatile unsigned long startTime; 

const int chipSelect = 4;
boolean isSDCard = false;
void setup() {
   Serial.begin(9600);
   Wire.begin();
   rtc.begin();
   LastInterrupt[0] = millis();
   LastInterrupt[1] = millis();
   pinMode(2,INPUT_PULLUP);
   pinMode(3,INPUT_PULLUP);
   pinMode(LEFT_LED,OUTPUT);
   pinMode(RIGHT_LED,OUTPUT);
   pinMode(PWR,OUTPUT);
   if (SD.begin(chipSelect)) {
        isSDCard = true;
   }
   DateTime cur = rtc.now(); 
   initTime = cur.unixtime(); 
   startTime = millis();
   attachInterrupt(0,ISR0,CHANGE);
   attachInterrupt(1,ISR1,CHANGE);
   digitalWrite(PWR,HIGH);
   ISR0();
   ISR1();
}


void logTime(File file) {
 if (file) {
    unsigned long elapsed = millis()-startTime;
    elapsed = elapsed/1000;
    DateTime now = DateTime(initTime + elapsed);
    file.print(now.year(), DEC);    
    file.print('/');
    file.print(now.month(), DEC);
    file.print('/');
    file.print(now.day(), DEC);
    file.print(' ');
    file.print(now.hour(), DEC);
    file.print(':');
    file.print(now.minute(), DEC);
    file.print(':');
    file.print(now.second(), DEC);
 }
}

//volatile int isDirty[] = {0,0};

void ISR0() {
 InterruptTime0 = millis();
 CheckState(InterruptTime0,0);
} // ISR has to be run quick, the code inside should be short

void ISR1() {
 InterruptTime1 = millis();
 CheckState(InterruptTime1,1);
}

void CheckState(unsigned long Time, int InterruptNum){
  ToiletState[InterruptNum] = !digitalRead(InterruptNum+2);
 if(Time - LastInterrupt[InterruptNum] > block){
   LastInterrupt[InterruptNum] = Time;
   digitalWrite(InterruptNum==0 ? LEFT_LED:RIGHT_LED,ToiletState[InterruptNum]);
  if(ToiletState[InterruptNum] == HIGH) {
    Serial.print(InterruptNum==0 ? "4":"6");    
  } else { 
    Serial.print(InterruptNum==0 ? "3":"5");
  }
  writeSD(InterruptNum);
 }
}

void writeSD(int idx) {
    if(isSDCard==true) {
             File dataFile = SD.open("datalog.txt", FILE_WRITE);
             if (dataFile) {
               logTime(dataFile);
               dataFile.print(",");
               dataFile.print(idx==0 ? "R":"L");
               dataFile.print(",");
               dataFile.println(ToiletState[idx]);
               dataFile.close();
            }
    }
}


void loop() {
}



