#include <Arduino.h>
#include "SPI.h"
#include "ADNS3080.h"
#include <vector>
#include "pid.h"
#include "Drive.h"
#include <Robojax_L298N_DC_motor.h>
#include<stdio.h>
#include"MPU6050_light.h"


int radar_Pin = 22;
int NumOfTest = 5;
float radar_amp;
float time_2cm;
String mode;
String command;
PID pidpointer;
MPU6050 mpu(Wire);
unsigned long timer = 0;
int facing_angle=0;

Robojax_L298N_DC_motor car(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB);






void setup()
{  Serial.begin(115200);
ADNS3080_set(PIN_SS, PIN_MISO, PIN_MOSI, PIN_SCK);

PID_init(&pidpointer,0.04,0.01,0.01);
Wire.begin();
  
  byte status = mpu.begin(1,0);
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(true,true); // gyro and accelero
  mpu.setFilterGyroCoef(0.98);
  Serial.println("Done!\n");
car.begin();
delay(1000);
}

int angle = 0;

void loop(){

mpu_rotate(0,45,mpu,car);
delay(10000);

    /*     facing_angle = -90;
        car.rotate(1,50,2);
        car.rotate(2,50,1);
        angle = mpu.getAngleZ();
        while(angle > facing_angle){
            mpu.update();
            Serial.println(angle);
            angle = mpu.getAngleZ();
        }
        car.brake(1);
        car.brake(2);
        facing_angle -= 90;
delay(1000);
 */
// mpu.update();
// car.rotate(1,30,2);
// car.rotate(2,30,1);
// Serial.println(mpu.getAngleZ());

//  if(mpu.getAngleZ()-facing_angle <90){
//    car.rotate(1,30,1);
//    car.rotate(2,30,2);
//  }
//  else{
//    facing_angle += 90;
//    car.brake(1);
//    car.brake(2);
//    delay(5000);
// } 

/* mpu.update();


  if(millis() - timer > 100){ // print data every second
    Serial.print(F("TEMPERATURE: "));Serial.println(mpu.getTemp());
    Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX());
    Serial.print("\tY: ");Serial.print(mpu.getAccY());
    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
  
    Serial.print(F("GYRO      X: "));Serial.print(mpu.getGyroX());
    Serial.print("\tY: ");Serial.print(mpu.getGyroY());
    Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
  
    Serial.print(F("ACC ANGLE X: "));Serial.print(mpu.getAccAngleX());
    Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
    
    Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    Serial.println(F("=====================================================\n"));
    timer = millis();
  } */
 
/* if(mode=="auto"){
     
        
     
      do{
        num0 = travel(20,1,70,&pidpointer,car);
        }while(num0==0);
      num0 = 0;



//-------------------------------loop----------------------------------------------
  for(int i = 0; i < 2; i++){ //whole loop
    for(int j = 0; j < 3; j++)
    {   //long distance
      do{
       num0 = travel(10,1,70,&pidpointer,car);
      }while(num0==0);
      num0 = 0;
      
      
    }

    do{
      num0 = rotate(0,90,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

    do{
      num0 = travel(10,1,70,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

    do{
      num0 = rotate(0,90,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

    for(int j = 0; j < 3; j++){
      do{
        num0 = travel(10,1,70,&pidpointer,car);
      }while(num0==0);
      num0 = 0;
    }
    do{
      num0 = rotate(1,90,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

    do{
      num0 = travel(10,1,70,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

    do{
      num0 = rotate(1,90,&pidpointer,car);
    }while(num0==0);
    num0 = 0;
  }
  
//////////////////////////////////////////////////////////////////////////////////////////////////

  for(int j = 0; j < 3; j++){   //long distance
 
      do{
        num0 = travel(10,1,70,&pidpointer,car);
      }while(num0==0);
      num0 = 0;  
    }
  

    do{
      num0 = rotate(0,90,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

    do{
      num0 = travel(10,1,70,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

    do{
      num0 = rotate(0,90,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

    for(int j = 0; j < 3; j++){
      do{
        num0 = travel(10,1,70,&pidpointer,car);
      }while(num0==0);
      num0 = 0;
    }

  do{
        num0 = travel(20,1,70,&pidpointer,car);  
      }while(num0==0);
      num0 = 0;

  do{
      num0 = rotate(0,90,&pidpointer,car);
    }while(num0==0);
    num0 = 0;

  for(int j = 0; j < 5; j++){
      do{
        num0 = travel(10,1,70,&pidpointer,car);
      }while(num0==0);
      num0 = 0;
    }
  delay(10000);
  }

  if(mode=="manual")
  {
    manualcontrol(command,&pidpointer);
  } 
 */
/* wangqian(&pidpointer);



//-------------------------------loop----------------------------------------------
  for(int i = 0; i < 2; i++){ //whole loop
    for(int j = 0; j < 3; j++)
    {   //long distance
      wangqian(&pidpointer);
    }

     right90(&pidpointer);

     wangqian(&pidpointer);

    right90(&pidpointer);

    for(int j = 0; j < 3; j++){
    wangqian(&pidpointer);
    }
      left90(&pidpointer);

   wangqian(&pidpointer);

    left90(&pidpointer);
  }
  
//////////////////////////////////////////////////////////////////////////////////////////////////

  for(int j = 0; j < 3; j++){   //long distance
 
     wangqian(&pidpointer);
    }
  

    right90(&pidpointer);

   wangqian(&pidpointer);





   right90(&pidpointer);

    for(int j = 0; j < 3; j++){
   wangqian(&pidpointer);
    }

    wangqian(&pidpointer);

  right90(&pidpointer);

  for(int j = 0; j < 5; j++){
     wangqian(&pidpointer);
    }
  delay(10000); */

  //car.rotate(2,50,1);


 
 // travel(50,1,70,&pidpointer,car);

   

}



  
// //travel 10 block
// //turn right 90
// //travel 1 block
// //turn right 90

// int NumOfBlock_Y = 13;
// int NumOfBlock_X = 6; //even number
// float radar;
// int detected = 0;

// //N = 1
// //move NumOfBlock_Y-1 
// //turn right
// //move 1
// //turn right


// //move NumOfBlock_Y-2
// //turn left
// //move 1
// //turn left
// //move NumOfBlock_Y-2
// //turn right
// //move 1
// //turn right

// //repeat for X/2-1 times


// //N = NumOfBlock_X
// //move NumOfBlock_Y-1
// //turn right
// //move NumberOfBlock_X-1
// //turn right






// for(int i=0; i<2; i++){
//   int flag = 0;
// } 




// int flag = 0;

// while(flag != 1){

// }