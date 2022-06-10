#ifndef _PID_H_
#define _PID_H_
 
struct PID{
float reference_value;
float actual_value;
float err;
float err_next;
float err_last;
float Kp, Ki, Kd;
float duty_cycle;
};
 
 
class Pid_control
{
public:
 
void PID_init(PID *a, float kp, float ki, float kd);
float PID_realize(PID*a,float reference_value, float actual_value);
 
private:
int index;
PID pid;
};
#endif

//https://blog.csdn.net/wzhCAlex/article/details/69945036?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_utm_term~default-0-69945036-blog-73824173.pc_relevant_default&spm=1001.2101.3001.4242.1&utm_relevant_index=3//