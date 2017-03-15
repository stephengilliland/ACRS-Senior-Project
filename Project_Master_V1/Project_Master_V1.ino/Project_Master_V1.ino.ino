const int chipSelect = 4; 
#include "TinyGPS.h"
#include<SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include "SD.h"

#define RXPIN 8
#define TXPIN 7
#define LOGFILE "datalog.txt"

SoftwareSerial nss(RXPIN, TXPIN);
File dataFile;
TinyGPS gps;



int x, i, error, data, ndevices, counter, current, requestdata = 0;
float PH, AL, TR, TP, CH = 0;
unsigned long fix_age, Time, date;
unsigned long chars;
unsigned short sentences, failed_checksum;
char sensortype = '0';
int device[10];
bool done=false;

void setup() {
  // put your setup code here, to run once:
  nss.begin(9600);
  
  Wire.begin(); 
  
  Serial.begin(9600);
  while(!Serial){}
  Serial.print("$$$");
  delay(100);
  Serial.println("SM,0");
  delay(100);
  Serial.println("U,115200,N");
  delay(100);
  Serial.begin(9600);
  delay(100);

  Serial.println("Initializing datalogger");
  Serial.println("Starting SDCard");
  pinMode(chipSelect, OUTPUT);
  pinMode(SS, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  
  Serial.println("Opening logfile for write.");
  // Open up the file we're going to log to!
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening log file");
    // Wait forever since we cant write data
    while (1) ;
  }
  dataFile.close();
  
  // Discover Devices
  for( i=1; i<128; i++ )
  {
    Wire.beginTransmission(i);
    error = Wire.endTransmission();
    if(error == 0)
    {
      ndevices ++;
    }
  }
  device[ndevices];
  
  // Discover Devices
  for(i=1; i<127; i++)
  {
    Wire.beginTransmission(i);
    error = Wire.endTransmission();
    if(error == 0)
    {
      device[counter] = i;
      counter++;
    }
  }
  Serial.print(ndevices);
  Serial.println(" Devices Found At Addresses: ");
  for( i=0;i<ndevices;i++ )
  {
    Serial.println(device[i]);  
  }
  Serial.println(" ");
}

void loop() {
  // put your main code here, to run repeatedly: 
   
  char tempS[7]; //2 int, 2 dec, 1 point, and \0
  char phS[7]; 
  char tripS[7];
  char chlorineS[7]; 
  char alkS[7];
  char msg[25];
  i = 0;
  counter = 0;
  
  while(done==false && counter<100)
  {
    while (nss.available())
    {
      int c = nss.read();
      if (gps.encode(c))
      {
        // process new gps info here
      }
    }  
    delay(10);
    // time in hhmmsscc, date in ddmmyy
    gps.get_datetime(&date, &Time, &fix_age);
    //Serial.println("Date/Time:");
    //Serial.println(Time);
    //Serial.println(date); 
    //Serial.println(counter); 
    counter++; 
  }
  done=true;

  // Get GPS Data
  while (nss.available())
  {
    int c = nss.read();
    if (gps.encode(c))
    {
      // process new gps info here
    }
  }  

  // Read Device Info
  for( i=0;i<ndevices;i++ )
  {
    Serial.print("Loop Number:  ");
    Serial.println(i);
    current = device[i];
    
    Wire.requestFrom(current, 1);    // request 1 byte from slave devices
    while (Wire.available())   // slave may send less than requested
    {
      sensortype = (char)Wire.read(); // receive a byte as character
    }

    Wire.requestFrom(current, 1);    // request 1 byte from slave devices
    while (Wire.available())   // slave may send less than requested
    {
      data = Wire.read(); // receive a byte as character
    }

    
    if(sensortype == 'P') // pH Sensor
    {
      PH = (float) data/10;
      Serial.print("Sensor Type = ");
      Serial.println("pH");
      Serial.print("pH = ");
      Serial.println(PH);
      Serial.println(" ");
    }
    if(sensortype == 'T') // Tribitiy Sensor
    {
      TR = data;
    }
    if(sensortype == 'A') // pH Sensor
    {
      AL = data;
      Serial.print("Sensor Type = ");
      Serial.println("Alkalenity");
      Serial.print("Alk = ");
      Serial.println(AL);
      Serial.println(" ");
    }
    if(sensortype == 'F') // pH Sensor
    {
      TP = data;
      Serial.print("Sensor Type = ");
      Serial.println("Temperature");
      Serial.print("temperature = ");
      Serial.println(TP);
      Serial.println(" ");
    }

   
  } 
  
   Serial.println("Done Looping");

   Serial.println(TP);
   Serial.println(PH);
   Serial.println(AL);
   Serial.println(CH);
   ftoa(tempS,TP);
   ftoa(phS,PH);
   ftoa(tripS,TR);
   ftoa(chlorineS,CH);
   
   sprintf(msg,"%s,%s,%s,%s",tempS, phS, tripS, chlorineS);
   //Serial.println(msg);
   logThis(msg); 
   delay(1000);
}

void logThis(char* logmessage){
  char message[75];
  gps.get_datetime(&date, &Time, &fix_age);
  //Serial.println(Time);
  //Serial.println(date);
  sprintf(message,"%lu,%lu,%s",date,Time,logmessage);
  //Write the entry to the log file and console
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(message);
    dataFile.close();
    // print to the serial port too:
    Serial.println(message);
  }
  else
    Serial.println("Error opening log file");
}

int ftoa(char *a, float f)  //translates floating point readings into strings
{
  int left=int(f);
  float decimal = f-left;
  int right = decimal *100; //2 decimal points
  if (right > 10) {  //if the decimal has two places already. Otherwise
    sprintf(a, "%d.%d",left,right);
  } else { 
    sprintf(a, "%d.0%d",left,right); //pad with a leading 0
  }
}
