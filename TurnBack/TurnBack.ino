/*
 Main Program For CarBot
 Including IR sensor, Collision sensor, Motor, Servo
 
 Copyright @ InfiniteSense.com
*/

#include <Servo.h> 

/* ir pin */
#define PIN_IR1_LEFT A0
#define PIN_IR2_LEFT A1
#define PIN_IR3_LEFT A2
#define PIN_IR3_RIGHT A3
#define PIN_IR2_RIGHT A4
#define PIN_IR1_RIGHT A5

/* collision pin */
#define PIN_COLLISION_IR 3

/* servo pin */
#define PIN_SERVO 2

#define IR_NUM 6
#define IR_NUM_MAX 6

#define STATE_TO_TOWER 0
#define STATE_TO_HOME 1
#define STATE_POST_BALL 2
#define STATE_FINDING_LINE 3


int collision_ir = 0;
int ir_array[IR_NUM] = { 0 };
const int ir_pin_array[IR_NUM_MAX] = {
   PIN_IR1_LEFT, PIN_IR2_LEFT, PIN_IR3_LEFT, PIN_IR3_RIGHT, PIN_IR2_RIGHT, PIN_IR1_RIGHT
};
const int ir_pos_map[IR_NUM_MAX] = {
    -5, -3, -1, 1, 3, 5
};

int car_direction = STATE_TO_TOWER;
Servo myservo;

void setup()
{
  initSerial();
  initMotor();
  initIR();
  initServo();
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
  if (collision_ir == LOW) {
    car_direction = STATE_FINDING_LINE;
    stopDead(1000);
    driveMotor();
    delay(1000);
    myservo.write(45);
    delay(1000);
    runLeft(180, 2);
    for (i = 0; i < 6000; i++) {
      driveMotor();
    }
    return;
  }
  if (ir_array[0] == HIGH && ir_array[1] == HIGH && ir_array[2] == HIGH && ir_array[3] == HIGH && ir_array[4] == HIGH) {
    runLeft(120, 2);
  } else {
    car_direction = STATE_TO_HOME;
    stopDead(1000);
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
     ir_array[i] = digitalRead(ir_pin_array[i]);
  }
  collision_ir = digitalRead(PIN_COLLISION_IR);
}
