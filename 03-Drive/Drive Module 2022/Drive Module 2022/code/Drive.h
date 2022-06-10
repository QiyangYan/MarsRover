#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include "Robojax_L298N_DC_motor.h"
#include "pid.h"
#include <vector>


// motor 1 settings
#define CHA 0
#define ENA 17 //D8 PWMA Athis pin must be PWM enabled pin if Arduino board is used
#define IN1 16 //D9 AIN2
#define IN2 14 //D10 AIN1
// motor 2 settings
#define IN3 4 //D11
#define IN4 15 //D12
#define ENB 2 //D13 PWMB this pin must be PWM enabled pin if Arduino board is used
#define CHB 1
const int CCW = 2; // do not change
const int CW  = 1; // do not change
#define motor1 1 // do not change
#define motor2 2 // do not change




void gostraight(int direction, float duty, std::vector<float> D);
int rotate90(int direction, int turndirection, std::vector<float> D);//turndirection=0 to CCW 90, turndirection=1 to CW 90
void zouduoyuan(int distance, int direction, int duty, std::vector<float>D);



#endif