#include <Arduino.h>
#include "Robojax_L298N_DC_motor.h"
#include "pid.h"
#include "Drive.h"
#include <vector>

Pid_control PID_control;
PID d;

Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB);
float frame_x=0;//need to measure
float frame_y=0;//need to measure
void moveforward(int speed)
{
robot.rotate(1,speed,1);
robot.rotate(2,speed,1);
};

void turnleft90(int speed)
{
robot.rotate(1,speed,1);
robot.rotate(2,speed,2);

};

void turnright90(int speed)
{
robot.rotate(1,speed,2);
robot.rotate(2,speed,1);
};

void stop()
{
robot.brake(1);
robot.brake(2);
}

//direction=0 when follow x direction
//direction=1 when follow y direction
//D is a vector contain total_x, total_y, dx, dy
//PID gives the moderation of the duty cycle which is the speed for the motor go from one positon to others
//duty is the required speed from the control, put in three level high=80, mid =60, low=40 (need to check)


void gostraight(int direction, float duty,  std::vector<float> D) 
//keep the car move straghly in x or y direction
// 1.travel direction,2. travel spped, 3.pid control, 4.results form sensor flow
{
if(direction ==0)// follow x direction 
{if(D[2]=0)
{
    moveforward(duty);// default moveforward
}
else
{
    float moderation=PID_control.PID_realize(&d, 0, D[2]);
    robot.rotate(1,duty+moderation,1); // remain the speed 
    robot.rotate(2,duty+moderation,1);// change the speed
}
}
else if(direction==1)// follow y direction 
{
    if(D[3]=0)
{
    moveforward(duty);// default moveforward
}
else
{
    float moderation= PID_control.PID_realize(&d,0, D[3]);
    robot.rotate(1,duty-moderation,1); // remain the speed 
    robot.rotate(2,duty+moderation,1);// change the speed
}
};
};


 
void zouduoyuan(int distance, int direction,int duty,std::vector<float> D)
//the car will go straight for certain distance
{
float initial_x=D[0];
float initial_y=D[1];
if(direction==0)//follow direction x
{//when the car moves forward in x direction for certain distance then stop
float moderation=PID_control.PID_realize(&d, initial_x+distance, D[0]);
while (D[1]!=initial_x+distance)
{
 gostraight(direction,duty, D);

}
stop();

}
else if(direction==1)// follow direction y
{//when the car moves forward in y direction for certain distance then stop
float moderation=PID_control.PID_realize(&d,  initial_y+distance, D[1]);
while (D[2]!=initial_y+distance)
{
 gostraight(direction,duty,  D);  
}
stop();

}

};

/*int rotate90(int direction, int turndirection, std::vector<float> D, PID_incre *PID)//turndirection=0 to CCW 90, turndirection=1 to CW 90
{
    float initial_x=D[0];
    float initial_y=D[1];
    float initial_dx=D[2];
    float initial_dy=D[3];
// car frame都是长度
//判断条件，原行驶方向，将要转动方向
//输入：D，转动指令，行驶方向
//输出：转动后方向

    switch(direction)
    { 
        case 0: 
            if (D[3]>=0)//positive y direction 
            {  if (turndirection =0)//CCW
                    {
                        float moderation=pid_control(PID, initial_y+1/2*frame_y, D[1]);
                        robot.rotate(1,moderation,1); //change the speed
                        robot.rotate(2,moderation,2);// change the speed, two motor rotates in opposite directon
                        while (D[1]=initial_y+1/2*frame_y)
                            {
                            stop();
                            break;
                            }
                        return direction=1;
                    }
                else  (turndirection=1);// CW
                    {
                        float moderation=pid_control(PID, initial_y+1/2*frame_y, D[1]);
                        robot.rotate(1,moderation,2); //change the speed
                        robot.rotate(2,moderation,1);// change the speed, two motor rotates in opposite directon
                        while (D[1]=initial_y+1/2*frame_y)
                            {
                            stop();
                            break;
                            }
                        return direction=1;
                    }

            } 
            else if(D[3]<=0)// negative y direction 
            {
                 if (turndirection =0)//CCW
                    {
                        float moderation=pid_control(PID, initial_y-1/2*frame_y, D[1]);
                        robot.rotate(1,moderation,1); //change the speed
                        robot.rotate(2,moderation,2);// change the speed, two motor rotates in opposite directon
                        while (D[1]=initial_y-1/2*frame_y)
                            {
                            stop();
                            break;
                            }
                        return direction=1;
                    }
                else  (turndirection=1);// CW
                    {
                        float moderation=pid_control(PID, initial_y-1/2*frame_y, D[1]);
                        robot.rotate(1,moderation,2); //change the speed
                        robot.rotate(2,moderation,1);// change the speed, two motor rotates in opposite directon
                        while (D[1]=initial_y-1/2*frame_y)
                            {
                            stop();
                            break;
                            }
                        return direction=1;
                    }

                
            }
        case 1:
        if (D[2]>=0)//positive x direction 
            {  if (turndirection =0)//CCW
                    {
                        float moderation=pid_control(PID, initial_y+1/2*frame_y, D[1]);
                        robot.rotate(1,moderation,1); //change the speed
                        robot.rotate(2,moderation,2);// change the speed, two motor rotates in opposite directon
                        while (D[1]=initial_y+1/2*frame_y)
                            {
                            stop();
                            break;
                            }
                        return direction=0;
                    }
                else  (turndirection=1);// CW
                   {
                        float moderation=pid_control(PID, initial_y-1/2*frame_y, D[1]);
                        robot.rotate(1,moderation,1); //change the speed
                        robot.rotate(2,moderation,2);// change the speed, two motor rotates in opposite directon
                        while (D[1]=initial_y-1/2*frame_y)
                            {
                            stop();
                            break;
                            }
                        return direction=0;
                    }

            } 
        else if (D[2]<=0)//positive x direction 
            {  if (turndirection =0)//CCW
                    {
                        float moderation=pid_control(PID, initial_y-1/2*frame_y, D[1]);
                        robot.rotate(1,moderation,1); //change the speed
                        robot.rotate(2,moderation,2);// change the speed, two motor rotates in opposite directon
                        while (D[1]=initial_y-1/2*frame_y)
                            {
                            stop();
                            break;
                            }
                        return direction=0;
                    }
                else(turndirection=1);// CW
                   {
                        float moderation=pid_control(PID, initial_y+1/2*frame_y, D[1]);
                        robot.rotate(1,moderation,1); //change the speed
                        robot.rotate(2,moderation,2);// change the speed, two motor rotates in opposite directon
                        while (D[1]=initial_y+1/2*frame_y)
                            {
                            stop();
                            break;
                            }
                        return direction=0;
                    }

            } 

}
//原行驶方向为follow positivie y direction 
//右转90°， D[2]变到等于转向前D[2]+car frame的一半
//左转90°，和上面一样，但是motor转动方向相反

//原行驶方向为follow negative y direction
//左转90°，D[2]变到转向前D[2]-car fram的一半
//右转90°，和上面一样， 但motor转动方向相反

//原行驶方向为follow poistive x direction
//右转90°需要, D[2]变到等与转向前D[2]+car frame的一半
//左转90°需要，D[2]变到等于转向前D[2]-car frame的一半

//原行驶方向为 follow negative x direction
//右转90°需要，D[2]变到等于转向前D[2]-car frame的一半
//左转90°需要，D[2]变到等于转向前D[2]+car frame的一半
};
*/


