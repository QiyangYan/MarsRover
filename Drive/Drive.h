#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include "Robojax_L298N_DC_motor.h"
#include "pid.h"
#include <vector>
#include "ADNS3080.h"
#include "MPU6050_light.h"


// motor 1 settings
#define CHA 0
#define ENA 27 //A0//17 //D8 PWMA Athis pin must be PWM enabled pin if Arduino board is used
#define IN1 26 //A1//16 //D9 AIN2
#define IN2 14 //D10 AIN1
// motor 2 settings
#define IN3 4 //D11
#define IN4 15 //D12
#define ENB 2 //D13 PWMB this pin must be PWM enabled pin if Arduino board is used
#define CHB 1
const int CCW = 2; // do not change
const int CW  = 1; // do not change
#define motor1 1 // do not change RHS

#define motor2 2 // do not change LHS



void gostraight(int direction,  PID *straightpointer,Robojax_L298N_DC_motor robot);

void rotatemanual(int direction,  PID *straightpointer,Robojax_L298N_DC_motor robot);

int rotate(/*int direction,*/ int turndirection, float degree, MPU6050 mpu,/*std::vector<float> D, */PID *rotatepointer,Robojax_L298N_DC_motor robot);//turndirection=0 to CCW 90, turndirection=1 to CW 90

int mpu_rotate(int turndirection,  float degree, MPU6050 mpu,Robojax_L298N_DC_motor robot);

int travel(int distance, int forward,int duty,/*std::vector<float> D,*/PID *distancepointer,Robojax_L298N_DC_motor robot);
/* 
void manualcontrol(String command,PID *manualpointer);

void wangqian(PID *pointer);

void right90(PID *pointer);

void left90(PID *pointer);
 */


#endif