#ifndef PID_incre_H
#define PID_incre_H

#include <Arduino.h>
 struct PID_incre
{
    float kp;
    float ki;
    float kd;
    float reference_value;
    float actual_value;
    float error;
    float error_pre1;
    float error_pre2;
    float integral;
    float duty_cycle;
    float A;
    float B;
    float C;
};

void pid_initial(PID_incre *PID, float kp,float ki,float kd);
float pid_control(PID_incre *PID, float reference_value,float actual_value);

#endif


/*//增量式PID
class PID_incremental
{
private:
    float kp;
    float ki;
    float kd;
    float target;
    float actual;
    float e;
    float e_pre_1;
    float e_pre_2;
    float A;
    float B;
    float C;
public:
    PID_incremental();
    PID_incremental(float p,float i,float d);
    float pid_control(float tar,float act);

};*/

/*typedef struct _pid{
float reference_value;
float actual_value;
float err;
float err_next;
float err_last;
float Kp, Ki, Kd;
}Pid;
 
 
class Pid_control
{
public:
 
void PID_init();
float PID_realize(float speed);
 
private:
int index;
Pid pid;
};

————————————————
版权声明：本文为CSDN博主「丫就是熊个猫猫」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/wzhCAlex/article/details/69945036*/