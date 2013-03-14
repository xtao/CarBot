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

#define IR1_LEFT 0
#define IR2_LEFT 1
#define IR2_RIGHT 2
#define IR1_RIGHT 3

/* collision pin */
#define PIN_COLLISION_IR 3

/* servo pin */
#define PIN_SERVO 8

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
    if (car_direction == STATE_TO_TOWER) {
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
    } else if (car_direction == STATE_TO_HOME) {
      stopDead(1000);
    }
    return;
  }
  if (car_direction == STATE_TO_TOWER) {
      // ir 5
      if (ir_array[0] == LOW && ir_array[2] == LOW) {
        runLeft(150, 2);
      } else if (ir_array[1] == LOW && ir_array[2] == LOW) {
        runLeft(120, 2);
      } else if (ir_array[2] == LOW) {
        runForward(150, 2);
      } else if (ir_array[1] == LOW) { 
        runLeft(120, 2);
      } else if (ir_array[3] == LOW) {
        runRight(120, 2);
      } else if (ir_array[0] == LOW) {
        runLeft(150 ,2);
      } else if (ir_array[4] == LOW) {
        runRight(150, 2);
      }
    } else if (car_direction == STATE_TO_HOME) {
      // ir 5
      if (ir_array[4] == LOW && ir_array[3] == LOW && ir_array[2] == LOW) {
        runRight(180, 2);
        // specific process
        for (i = 0; i < 6000; i++) {
          driveMotor();
        }
      } else if (ir_array[4] == LOW && ir_array[2] == LOW) {
        runRight(180, 2);
      } else if (ir_array[3] == LOW && ir_array[2] == LOW) {
        runRight(150, 2);
      } else if (ir_array[2] == LOW) {
        runByPosition(0, 2);
      } else if (ir_array[1] == LOW) {
        runByPosition(4, 2);
      } else if (ir_array[3] == LOW) {
        runByPosition(-4, 2);
      } else if (ir_array[0] == LOW) {
        runByPosition(6, 2);
      } else if (ir_array[4] == LOW) {
        runByPosition(-6, 2);
      }
    } else if (car_direction == STATE_FINDING_LINE) {
      if (ir_array[0] == HIGH && ir_array[1] == HIGH && ir_array[2] == HIGH && ir_array[3] == HIGH && ir_array[4] == HIGH) {
        runLeft(120, 2);
      } else {
        car_direction = STATE_TO_HOME;
      }
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
