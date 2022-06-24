#ifndef PID_H_
#define PID_H_
 
struct PID{
float reference_value;
float actual_value;
float error;
float error_last;
float kp, ki, kd;
float duty_cycle;
float integral_value;
float differential_value;
};
 



void PID_init(PID *u, float kp, float ki, float kd);


float PID_realize(PID*u,float reference_value, float actual_value);
 

#endif

//https://blog.csdn.net/shuoyueqishilove/article/details/73824173?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165369513516781432959181%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165369513516781432959181&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-73824173-null-null.142^v11^pc_search_result_control_group,157^v12^new_style1&utm_term=%E5%9F%BA%E4%BA%8Ec%2B%2B%E7%9A%84PID%E6%8E%A7%E5%88%B6%E5%99%A8&spm=1018.2226.3001.4https://blog.csdn.net/shuoyueqishilove/article/details/73824173?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165369513516781432959181%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165369513516781432959181&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-73824173-null-null.142^v11^pc_search_result_control_group,157^v12^new_style1&utm_term=%E5%9F%BA%E4%BA%8Ec%2B%2B%E7%9A%84PID%E6%8E%A7%E5%88%B6%E5%99%A8&spm=1018.2226.3001.4187https://blog.csdn.net/shuoyueqishilove/article/details/73824173?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165369513516781432959181%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165369513516781432959181&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-73824173-null-null.142^v11^pc_search_result_control_group,157^v12^new_style1&utm_term=%E5%9F%BA%E4%BA%8Ec%2B%2B%E7%9A%84PID%E6%8E%A7%E5%88%B6%E5%99%A8&spm=1018.2226.3001.4187187