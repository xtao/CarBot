#define PIN_PWM_LEFT 11
#define PIN_DIR_LEFT 10
#define PIN_PWM_RIGHT 13
#define PIN_DIR_RIGHT 12

void setup()
{
  pinMode(PIN_DIR_LEFT, OUTPUT);
  pinMode(PIN_DIR_RIGHT, OUTPUT);
}

void loop()
{
    analogWrite(PIN_PWM_LEFT, 120);
    digitalWrite(PIN_DIR_LEFT, HIGH);
    
    delay(1000);
    
    analogWrite(PIN_PWM_LEFT, 0);
    digitalWrite(PIN_DIR_LEFT, HIGH);
    
    delay(1000);
    
    analogWrite(PIN_PWM_RIGHT, 120);
    digitalWrite(PIN_DIR_RIGHT, HIGH);
    
    delay(1000);
    
    analogWrite(PIN_PWM_RIGHT, 0);
    digitalWrite(PIN_DIR_RIGHT, HIGH);
    
    delay(1000);
   
}
