/*
 PID 
 Copyright @ InfiniteSense.com
*/

#define PID_P_FACTOR 5.9
#define PID_I_FACTOR 0
#define PID_D_FACTOR 0
#define PID_SCALING_FACTOR 128

struct pid_t {
  int p_factor;
  int i_factor;
  int d_factor;
  int sum_error;
  int last_error;
};

struct pid_t pid = {
  PID_P_FACTOR * PID_SCALING_FACTOR,
  PID_I_FACTOR * PID_SCALING_FACTOR,
  PID_D_FACTOR * PID_SCALING_FACTOR,
  0,
  0
};

int processPID(int setPoint, int processValue, struct pid_t *pid)
{
    int error = 0;
    int p_term = 0;
    int i_term = 0;
    int d_term = 0;
    int ret = 0;
    error = setPoint - processValue;
    p_term = pid->p_factor * error;
    //pid->sum_error = pid->sum_error + error;
    //i_term = pid->i_factor * pid->sum_error;
    d_term = pid->d_factor * (pid->last_error - error);
    pid->last_error = error;
    ret = (p_term + i_term + d_term) / PID_SCALING_FACTOR;
    /* TODO: check value range */
    return ret;
}
