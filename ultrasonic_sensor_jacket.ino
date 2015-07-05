#include "Ultrasonic.h"
#include "MyUltrasonic.h"
#include <Grove_LED_Bar.h>
#include <SPI.h>
#include <SD.h>
//   背中
//--------------
// LT    RT
//
// LB    RB
//--------------

enum sensorIndex{
  cLB = 0,
  cRB = 1,
  cLT = 2,
  cRT = 3
};

MyUltrasonic LB(5);
MyUltrasonic RB(6);
MyUltrasonic LT(7);
MyUltrasonic RT(8);
Grove_LED_Bar bar(3, 2, 0);  // Clock pin, Data pin, Orientation

long datas[4] = {400,400,400,400};
long lbRange=0;
long rbRange=0;
long ltRange=0;
long rtRagne=0;

int currentNumber = 0;
int minSensor = cLB;

bool first = true;

void setup()
{
	Serial.begin(9600);
        pinMode(4, OUTPUT);
        delay(500);
}

void loop()
{  
        if (first){
            Serial.print("upperleft");
            Serial.print(",");
            Serial.print("upperright");
            Serial.print(",");
            Serial.print("lowerleft");
            Serial.print(",");
            Serial.print("lowerright");
            Serial.print(",");
            Serial.print("MinimumRange");
            Serial.println("");
            first = false;
        }
        //printDistance(LB, "LB");
        datas[cLB] = LB.MeasureInCentimeters();
        datas[cRB] = RB.MeasureInCentimeters();
        datas[cLT] = LT.MeasureInCentimeters();
        datas[cRT] = RT.MeasureInCentimeters();
        //Serial.println(datas[0]);
        
        long minDistance = getMinDistance();
        filterDistance();
        
        printData(minDistance);   
        boolean checkObject = detectObject(minDistance);
	
        if(checkObject){
            //Serial.println("cehck object");
            digitalWrite(4, HIGH);  
        }else{
            digitalWrite(4, LOW); 
        }
        //
        //analogWrite(4, 255);
        delay(10);
}

void printData(long miniDistance){
  Serial.print(datas[cLB]);
  Serial.print(",");
  Serial.print(datas[cRB]);
  Serial.print(",");
  Serial.print(datas[cLT]);
  Serial.print(",");
  Serial.print(datas[cRT]);
  Serial.print(",");
  Serial.print(miniDistance);
  Serial.println("");
}

void printDistance(MyUltrasonic ultrasonic, char* sensorname){
  long centi = ultrasonic.MeasureInCentimeters();
  int led_value = 10 - centi/40;
  Serial.print(sensorname);
  Serial.print("  :  ");
  Serial.print(centi);//0~400cm
  Serial.print(" cm : ");
  Serial.print(led_value);
  Serial.println(" ");
}

long getMinDistance(){
   return fmin( fmin(datas[cLB],datas[cRB]), fmin(datas[cLT],datas[cRT]));
}

boolean detectObject(long distance){
   boolean detect = true;
   if(distance < 40){
    
   }else if (distance < 80){
     
   }else if(distance < 120){
       
   }else if(distance < 200){
     
   }else{
     detect = false;
   }
   return detect;
}

void activateVibration(){
}

void filterDistance(){
    if(datas[cLB] > 200) {
       datas[cLB] = 0; 
    }
    if(datas[cRB] > 200) {
       datas[cRB] = 0; 
    }
    if(datas[cLT] > 200) {
       datas[cLT] = 0; 
    }
    if(datas[cRT] > 200) {
       datas[cRT] = 0; 
    }
}
