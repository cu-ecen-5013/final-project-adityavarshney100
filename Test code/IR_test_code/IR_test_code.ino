int IRSensor = 2; // connect ir sensor to arduino pin 2
int LED = 13; // conect Led to arduino pin 13



void setup() 
{
  Serial.begin(9600);
  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // Led pin OUTPUT
}

void loop()
{
  int Sensor_status = digitalRead (IRSensor);
  Serial.println(Sensor_status);
  if (Sensor_status == 0)
  {
    digitalWrite(LED, HIGH); // LED LOW
  }
  
  else
  {
    digitalWrite(LED, LOW); // LED High
  
  }
  
}
