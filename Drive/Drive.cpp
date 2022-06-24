#include <Arduino.h>
#include "Robojax_L298N_DC_motor.h"
#include "pid.h"
#include "Drive.h"
#include "ADNS3080.h"
#include <vector>
#include "MPU6050_light.h"




Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB);

float centreofrotation=12;




float total_x=0;
float total_y=0;

float total_x1 = 0;
float total_y1 = 0;

float changex=0;
float changey=0; 
int finished=0;
int num0=0;


void turnleft(int speed)
{
robot.rotate(1,speed,1);
robot.rotate(2,speed,2);

};

void turnright(int speed)
{
robot.rotate(1,speed,2);
robot.rotate(2,speed,1);
};

void stop()
{
robot.brake(1);
robot.brake(2);
}
void gostraight(int direction,  PID *manualpointer,Robojax_L298N_DC_motor robot) 
//keep the car move straghly in x or y direction
// 1.travel direction,2. travel speed, 3.pid control, 4.results form sensor flow
{ float duty=70;
    MD md;
    mousecam_read_motion(&md);
    star(md);//check the resolution
    changex = convTwosComp(md.dx);
    changey = convTwosComp(md.dy);
    total_x1 = total_x1 + changex;
    total_y1 = total_y1 + changey;
    total_x = total_x1/157*3.500;//*3.732;
    total_y = total_y1/157*3.700;
    std::vector<float> D {total_x,total_y,changex,changey};
if (direction==1) //go forward
{
float moderation= 100*PID_realize(manualpointer,0,D[0]);
robot.rotate(1,duty+moderation,1);
robot.rotate(2,duty-moderation,1);
}  
if (direction==0) //goback

{
float moderation= 100*PID_realize(manualpointer,0,D[0]) ;
robot.rotate(1,duty+moderation,2);
robot.rotate(2,duty-moderation,2);
}
}
void rotatemanual(int direction,  PID *manualpointer,Robojax_L298N_DC_motor robot) 
//keep the car move straghly in x or y direction
// 1.travel direction,2. travel speed, 3.pid control, 4.results form sensor flow

{ float duty=40;
                    MD md;
                    mousecam_read_motion(&md);
                    star(md);//check the resolution

                    changex = convTwosComp(md.dx);
                    changey = convTwosComp(md.dy);

                    total_x1 = total_x1 + changex;
                    total_y1 = total_y1 + changey;
                    
                    total_x = total_x1/157*3.500;//*3.732;
                    total_y = total_y1/157*3.700;
                    
                    std::vector<float> D {total_x,total_y,changex,changey};
                if (direction==0) //rightturn

                {
                float moderation= 100*PID_realize(manualpointer,0,D[0]) ;

                robot.rotate(1,duty+moderation,2);
                robot.rotate(2,duty-moderation,1);
                }


                if (direction==1) //leftturn

                {
                float moderation= 100*PID_realize(manualpointer,0,D[0]) ;

                robot.rotate(1,duty+moderation,1);
                robot.rotate(2,duty-moderation,2);
                }
 }
int travel(int distance, int forward,int duty,PID *distancepointer,Robojax_L298N_DC_motor robot)
//the car will go straight for certain distance
//forward=1 is forward, forward=0 is backward
//finished is the flag, then refresh the sensor 
{   MD md;
    mousecam_read_motion(&md);
    star(md);//check the resolution
    changex = convTwosComp(md.dx);
    changey = convTwosComp(md.dy);
    total_x1 = total_x1 + changex;
    total_y1 = total_y1 + changey;
    total_x = total_x1/157*3.500;//*3.732;
    total_y = total_y1/157*3.700;
    std::vector<float> D {total_x,total_y,changex,changey};
  if(forward==0){
    if (distance>abs(D[1]))
        {float moderation= 100*PID_realize(distancepointer,0,D[0]) ;
        
        robot.rotate(1,duty+moderation,2);
        robot.rotate(2,duty-moderation,2);}
    else{stop();
        total_x1=0;
        total_y1=0;
        finished=1;}
    }
   if(forward==1)
   {
    if(distance>abs(D[1]))
    {       
    float moderation= 100*PID_realize(distancepointer,0,D[0]) ;
    robot.rotate(1,duty+moderation,1);
    robot.rotate(2,duty-moderation,1);          
    }
    else
    {stop();
    total_x1=0;
    total_y1=0;
    finished=1;
    }
    }
    return finished;
}
int rotate(int turndirection,  float degree, MPU6050 mpu,PID *rotationpointer,Robojax_L298N_DC_motor robot)//turndirection=0 to the left, vice versa
 {
mpu.update();
int speed=40;
mpu.update();
float pi=3.1415926535;
mpu.update();
float radius=centreofrotation;
mpu.update();
float arclength=(degree/360)*2*pi*centreofrotation;
mpu.update();
//abs(x)is the arc length of the rotation produced by the optical sensor
MD md;
mpu.update();
mousecam_read_motion(&md);
mpu.update();
star(md);//check the resolution
mpu.update();
changex = convTwosComp(md.dx);
mpu.update();
changey = convTwosComp(md.dy);
mpu.update();
total_x1 = total_x1 + changex;
mpu.update();
total_y1 = total_y1 + changey;
mpu.update();
total_x = total_x1/157*3.500;//*3.732;
mpu.update();
total_y = total_y1/157*3.700;
mpu.update();
std::vector<float> D {total_x,total_y,changex,changey};
mpu.update();

Serial.println(String(mpu.getAngleZ()) + "   -------------------------------------");
  if(turndirection==0)//rightturn
         { mpu.update();
         if (90>abs(mpu.getAngleZ()))//positive y direction 
            {mpu.update();
            finished=0;
                   
                        float moderation=PID_realize(rotationpointer, 0, D[1]);
                        mpu.update();
                        robot.rotate(1,speed+moderation,2); //change the speed
                        mpu.update();
                        robot.rotate(2,speed-moderation,1);// change the speed, two motor rotates in opposite directon   
                        mpu.update();
             }
            else  
                    {
                     stop();
                     mpu.update();
                   total_x1=0;
                   mpu.update();
                   total_y1=0;
                   mpu.update();
                    finished=1;

                    delay(10000);
                    }
         }
      if(turndirection==1)//leftturn
          { if (degree>mpu.getAngleZ())//positive x direction 
                {finished=0;
                         float moderation=PID_realize(rotationpointer,0, D[1]);
                        robot.rotate(1,speed+moderation,1); //change the speed
                        robot.rotate(2,speed-moderation,2);
                }      
             else 
                 {

                    stop();
                total_x1=0;
                total_y1=0;
                finished=mpu.getAngleZ();
                delay(1000);
            ;   
                 }
            }mpu.update();
return finished;
}

int mpu_rotate(int turndirection,  float degree, MPU6050 mpu,Robojax_L298N_DC_motor robot){
    if(turndirection == 0){
        mpu.update();
        robot.rotate(1,50,2);
        robot.rotate(2,50,1);
        int angle = mpu.getAngleZ();
        while(angle < degree){
            mpu.update();
            Serial.println(angle);
            angle = mpu.getAngleZ();
        }
        robot.brake(1);
        robot.brake(2);
        mpu.update();
    }
    return mpu.getAngleZ();
}
      
/* void wangqian(PID *pointer)
{
    int num0=0;
    do{
        num0 = travel(40,1,70,pointer,robot);
        }while(num0==0);
     
}
void right90(PID *pointer)
{   
    int num0=0;
 do{
        num0 =  rotate(0,90,pointer,robot);
        }while(num0==0);
}

void left90(PID *pointer)
{   
    int num0=0;
 do{
        num0 =  rotate(1,90,pointer,robot);
        }while(num0==0);
} 

void manualcontrol(String command, PID *manualpointer)
{


    if(command=="stop")// stop button

        {stop();}

    if(command=="forward")//forward   

        { gostraight(1,manualpointer,robot);
        
        }

    if(command=="backward")//backward

        { gostraight(0,manualpointer,robot);}

    if(command=="left")//left

        {rotatemanual(1,manualpointer,robot);}


    if(command=="right")//right

        { rotatemanual(0,manualpointer,robot);}

}

 */
