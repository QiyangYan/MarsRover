#include <iostream>
#include "pid.h"
 
using namespace std;
 
void PID_init(PID *u, float kp, float ki, float kd)
{
u->actual_value = 0.0;
u->reference_value = 0.0;
u->integral_value=0.0;
u->differential_value=0.0;
u->error = 0.0;
u->error_last = 0.0;
u->kp = kp;
u->ki = ki;
u->kd = kd;
u->duty_cycle=0.0;
}
 
/*float PID_realize(PID*u,float target_value, float current_value ){
u->actual_value=current_value;
u->reference_value=target_value;
u->err = u->reference_value - u->actual_value;
u->duty_cycle = u->Kp*(u->err - u->err_next) + u->Ki*u->err + u->Kd*(u->err - 2 *u->err_next + u->err_last);

u->err_last = u->err_next;
u->err_next = u->err;
return u->duty_cycle;
}*/

float PID_realize(PID*u,float target_value, float current_value )
{
   /*  u->reference_value = target_value;
    u->actual_value  =current_value;
    u->err   = u->reference_value - u->actual_value;//0.8
    u->integral_value  = u->err + u->err_last;
    float P = u->err;
    float I = u->integral_value;
    float D = u->err - u->err_last;
    u->err_last = u->err;
    u->duty_cycle = u->Kp * P + u->Ki *I + u->Kd * D;
     */
 
    u->reference_value = target_value;
    u->actual_value  =current_value;
    u->error  = u->reference_value - u->actual_value;
    u->integral_value  = u->error + u->error_last;
    u->differential_value=u->error - u->error_last;
    u->error_last = u->error;
    u->duty_cycle = u->kp * u->error + u->ki* u->integral_value + u->kd* u->differential_value;
    return u->duty_cycle;
}

