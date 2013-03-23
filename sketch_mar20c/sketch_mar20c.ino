void setup()
{
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  analogWrite(11, 150);
  digitalWrite(10, HIGH);
  analogWrite(13, 150);
  digitalWrite(12, HIGH);
  delay(3000);
  analogWrite(11, 0);
  digitalWrite(10, HIGH);
  analogWrite(13, 0);
  digitalWrite(12, HIGH);
  delay(3000);
}
