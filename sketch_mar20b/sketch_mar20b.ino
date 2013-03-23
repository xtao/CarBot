
#define IR_NUM 4
int ir_max_array[IR_NUM] = { 0 };
int ir_min_array[IR_NUM] = { 32767, 32767, 32767, 32767 };

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int i;
  for (i = 0; i < IR_NUM; i ++) {
    Serial.println("Z");
    Serial.print(ir_max_array[i], DEC);
    Serial.print(ir_min_array[i], DEC);
    Serial.println("Z");
  }
  delay(1000);
}
