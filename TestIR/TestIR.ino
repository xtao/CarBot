
/* ir pin */
#define PIN_IR1_LEFT A3
#define PIN_IR2_LEFT A2
#define PIN_IR2_RIGHT A1
#define PIN_IR1_RIGHT A0

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_IR1_LEFT, INPUT);
  pinMode(PIN_IR2_LEFT, INPUT);
  pinMode(PIN_IR2_RIGHT, INPUT);
  pinMode(PIN_IR1_RIGHT, INPUT);
}

void loop()
{
  unsigned int v;
  v = analogRead(PIN_IR1_LEFT);
  Serial.print("LEFT1: ");
  Serial.print(v, DEC);
  Serial.println(" ");
  v = analogRead(PIN_IR2_LEFT);
  Serial.print("LEFT2: ");
  Serial.print(v, DEC);
  Serial.println(" ");
  v = analogRead(PIN_IR2_RIGHT);
  Serial.print("RIGHT2: ");
  Serial.print(v, DEC);
  Serial.println(" ");
  v = analogRead(PIN_IR1_RIGHT);
  Serial.print("RIGHT1: ");
  Serial.print(v, DEC);
  Serial.println(" ");
  delay(1000);
  
}

