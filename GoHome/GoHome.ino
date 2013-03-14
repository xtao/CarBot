/*
 Main Program For CarBot
 Including IR sensor, Collision sensor, Motor, Servo
 
 Copyright @ InfiniteSense.com
*/

#include <Servo.h> 

/* ir pin */
#define PIN_IR1_LEFT A3
#define PIN_IR2_LEFT A2
#define PIN_IR2_RIGHT A1
#define PIN_IR1_RIGHT A0

#define IR1_LEFT_THRESHOLD 350
#define IR2_LEFT_THRESHOLD 230
#define IR2_RIGHT_THRESHOLD 230
#define IR1_RIGHT_THRESHOLD 320

#define IR1_LEFT 0
#define IR2_LEFT 1
#define IR2_RIGHT 2
#define IR1_RIGHT 3

/* collision pin */
#define PIN_COLLISION_IR 8

/* servo pin */
#define PIN_SERVO 2

#define IR_NUM 4
#define IR_NUM_MAX 4

#define STATE_TO_TOWER 0
#define STATE_TO_HOME 1
#define STATE_POST_BALL 2
#define STATE_FINDING_LINE 3


int collision_ir = 0;
int ir_array[IR_NUM] = { 0 };
const int ir_pin_array[IR_NUM_MAX] = {
   PIN_IR1_LEFT, PIN_IR2_LEFT, PIN_IR2_RIGHT, PIN_IR1_RIGHT
};
const int ir_pos_map[IR_NUM_MAX] = {
    -3, -1, 1, 3
};

int car_direction = STATE_TO_TOWER;
Servo myservo;

void setup()
{
  initSerial();
  initMotor();
  initIR();
  //initServo();
  delay(1000);
}

void loop() 
{ 
  readIR();
  process();
  driveMotor();
}

void initServo()
{
  myservo.attach(PIN_SERVO);
  myservo.write(90);
}

void initSerial()
{
  Serial.begin(9600);
}

void process()
{
  int i;
  /* use 4 irs */
  if (ir_array[IR1_RIGHT] > IR1_RIGHT_THRESHOLD && ir_array[IR2_RIGHT] > IR2_RIGHT_THRESHOLD) {
    runRight(150, 2);
  } else if (ir_array[IR2_LEFT] > IR2_LEFT_THRESHOLD) {
    runByPosition(2, 2);
  } else if (ir_array[IR2_RIGHT] > IR2_RIGHT_THRESHOLD) {
    runByPosition(-2, 2);
  } else if (ir_array[IR1_LEFT] > IR1_LEFT_THRESHOLD) {
    runByPosition(6, 2);
  } else if (ir_array[IR1_RIGHT] > IR1_RIGHT_THRESHOLD) {
    runByPosition(-6, 2);
  } else {
    runByPosition(0, 2);
  }
}

/*
 IR Sensor
 */

void initIR()
{
  int i;
  // setting input pins
  for (i = 0; i < IR_NUM_MAX; i++) { 
    pinMode(ir_pin_array[i], INPUT);
  }
  pinMode(PIN_COLLISION_IR, INPUT);
}

int readIR()
{
  int i;
  for (i = 0; i < IR_NUM; i++) {
     ir_array[i] = analogRead(ir_pin_array[i]);
  }
  collision_ir = digitalRead(PIN_COLLISION_IR);
}
