/*
 MOTOR
 Copyright @ InfiniteSense.com
*/

/* pwm port 3, 5, 6, 9, 10, 11 */
#define PIN_PWM_LEFT 11
#define PIN_DIR1_LEFT 10
#define PIN_DIR2_LEFT 9
#define PIN_PWM_RIGHT 6
#define PIN_DIR1_RIGHT 5
#define PIN_DIR2_RIGHT 4

#define MOTOR_NUM 2
#define MOTOR_PWM 0
#define MOTOR_DIR1 1
#define MOTOR_DIR2 2
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

int motor_array[3][MOTOR_NUM] = { 0 };
long motor_delay = 0; // in us
const int motor_pin_array[3][MOTOR_NUM] = {
  {PIN_PWM_LEFT, PIN_PWM_RIGHT}, // digital PWM pins
  {PIN_DIR1_LEFT, PIN_DIR1_RIGHT},
  {PIN_DIR2_LEFT, PIN_DIR2_RIGHT}
};

void initMotor()
{
  int i;
  for (i = 0; i < MOTOR_NUM; i++) {
    pinMode(motor_pin_array[MOTOR_DIR1][i], OUTPUT);
    pinMode(motor_pin_array[MOTOR_DIR2][i], OUTPUT); 
  }
}

void runForward(int speed, int delay)
{
  motorForward(MOTOR_LEFT, speed);
  motorForward(MOTOR_RIGHT, speed);
  motor_delay = delay;
}

void runBackward(int speed, int delay)
{
  motorBackward(MOTOR_LEFT, speed);
  motorBackward(MOTOR_RIGHT, speed);
  motor_delay = delay;
}

void runLeft(int speed, int delay)
{
  motorBackward(MOTOR_LEFT, speed);
  motorForward(MOTOR_RIGHT, speed);
  motor_delay = delay;
}

void runRight(int speed, int delay)
{
  motorForward(MOTOR_LEFT, speed);
  motorBackward(MOTOR_RIGHT, speed);
  motor_delay = delay;
}

void stopDead(int delay)
{
  motorStop(MOTOR_LEFT);
  motorStop(MOTOR_RIGHT);
  motor_delay = delay;
}

void runByPosition(int position, int delay)
{
  if (position < -5) {
    motorForward(MOTOR_LEFT, 150);
    motorForward(MOTOR_RIGHT, 0);
  } else if (position >= -5 && position < -1) {
    motorForward(MOTOR_LEFT, 150); 
    motorForward(MOTOR_RIGHT, 30 * position + 180);
  } else if (position >= -1 && position <= 1) {
    motorForward(MOTOR_LEFT, 120);
    motorForward(MOTOR_RIGHT, 120);
  } else if (position > 1 && position <= 5) {
    motorForward(MOTOR_LEFT, -30 * position + 180);
    motorForward(MOTOR_RIGHT, 150);
  } else if (position > 5) {
    motorForward(MOTOR_LEFT, 0);
    motorForward(MOTOR_RIGHT, 150);
  }
  motor_delay = delay;
}

void motorForward(int motor, int speed)
{
  motor_array[MOTOR_PWM][motor] = speed;
  motor_array[MOTOR_DIR1][motor] = HIGH;
  motor_array[MOTOR_DIR2][motor] = LOW;
}

void motorBackward(int motor, int speed)
{
  motor_array[MOTOR_PWM][motor] = speed;
  motor_array[MOTOR_DIR1][motor] = LOW;
  motor_array[MOTOR_DIR2][motor] = HIGH;
}

void motorStop(int motor)
{
  motor_array[MOTOR_PWM][motor] = 0;
  motor_array[MOTOR_DIR1][motor] = HIGH;
  motor_array[MOTOR_DIR2][motor] = HIGH;
}

int driveMotor()
{
  int i;
  for (i = 0; i < MOTOR_NUM; i++) {
    analogWrite(motor_pin_array[MOTOR_PWM][i], motor_array[MOTOR_PWM][i]);
    digitalWrite(motor_pin_array[MOTOR_DIR1][i], motor_array[MOTOR_DIR1][i]);
    digitalWrite(motor_pin_array[MOTOR_DIR2][i], motor_array[MOTOR_DIR2][i]);
  }
  delayMicroseconds(motor_delay);
}
