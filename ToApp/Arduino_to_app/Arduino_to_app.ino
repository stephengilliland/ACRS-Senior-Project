
bool automode = false;
valuestr[20];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void sensorRead()
{
  sprintf(valuestr, "3.22,7.34,75.5,97")
}
void reportData()
{
  Serial.print(valuestr);
}
void loop() {
  // put your main code here, to run repeatedly:
  int command;
  while(Serial.available)
  {
      command = Serial.read();
  }
  if(command == '1')// Read Sensors
  {
    semsorRead();
    reportData();
  }
  if(command == '2')// Add Chemicals
  {
    addChem();
  }
  if(command == '3')// Set mode automatic
  {
    automode = true;
  }
  if(command == '4')// set mode manual
  {
    automode = false;
  }
}
