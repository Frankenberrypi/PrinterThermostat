//
// Written for the Arduino Nano, ATmega 328, 5.0V version
//
//**************************************************
// Temperature sensor stuff here
//**************************************************
#include <OneWire.h>
#include <DallasTemperature.h>

// Sensor plugged into digital port 3 on the arduino
#define ONE_WIRE_BUS 3
#define TEMPERATURE_PRECISION 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int numberOfDevices;
int idNum=0;
int sensorDelay=100;
char units='c';
DeviceAddress tempDeviceAddress;

//**************************************************
// LCD stuff here
//**************************************************
#include <Wire.h>
#include<LiquidCrystal_I2C.h>
// from https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

int thermostatSwitch = 11;

LiquidCrystal_I2C lcd(0x27,20,4); //set address to 0x27 for 20 characters and 4 lines

//**************************************************
// Thermostat stuff
//**************************************************
float lowSet=40;
int switchThermostat=0;
int relayPin8 = 8;

void setup(void)
{
  // start serial for debugging
  Serial.begin(9600);
  Serial.println("Begin debug");
  //**************************************************
  // Temp sensor stuff
  //**************************************************
  sensors.begin(); //start library
  //count devices
  numberOfDevices = sensors.getDeviceCount();
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices");
  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
  {
    Serial.print("Found device ");
    Serial.print(i, DEC);
    Serial.print(" with address: ");
    printAddress(tempDeviceAddress);
    Serial.println();
    
    Serial.print("Setting resolution to ");
    Serial.println(TEMPERATURE_PRECISION, DEC);
    
    // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
    sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
    
     Serial.print("Resolution actually set to: ");
    Serial.print(sensors.getResolution(tempDeviceAddress), DEC); 
    Serial.println();
  }else{
    Serial.print("Found ghost device at ");
    Serial.print(i, DEC);
    Serial.print(" but could not detect address. Check power and cabling");
  }
  }

  //**************************************************
  // LCD stuff
  //**************************************************
     //lcd.init();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(1,1);
  lcd.print("3D Printer Cabinet");
  lcd.setCursor(5,2);
  lcd.print("Thermostat");
  delay(2000);
  lcd.clear();
  Serial.println("End setup");

    //**************************************************
  // Thermostat stuff
  //**************************************************
  pinMode(relayPin8, OUTPUT);
}
void loop(void)
{
  //**************************************************
  // Temp sensor stuff
  //**************************************************
  // get temps for all devices on the bus
  sensors.requestTemperatures();
  // create an array to store temps
  float temps[numberOfDevices];
  // loop through devices and store temps
  for(int i=0;i<numberOfDevices; i++)
  {
    if(sensors.getAddress(tempDeviceAddress, i))
    {
      temps[i] = sensors.getTempC(tempDeviceAddress);
    }
  }
  // delay long enough for the sensors to refresh
  delay(sensorDelay);

  //**************************************************
  // LCD stuff
  //**************************************************
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temps[0]);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Setpoint: ");
  lcd.print(lowSet);
  lcd.print("C");

  //**************************************************
  // Thermostat stuff
  //**************************************************
  lcd.setCursor(0,2);
  if(digitalRead(thermostatSwitch) == HIGH)
  {
    lcd.print("Thermostat on ");
    lcd.setCursor(0,3);
    Serial.println("thermostat on");
    if (temps[0] < lowSet)
    {
      Serial.println("heater on");
      digitalWrite(relayPin8, HIGH);
      lcd.print("Heater on ");
    }
    else{
      Serial.println("heater off");
      digitalWrite(relayPin8, LOW);
      lcd.print("Heater off");
    }
  }else{
    Serial.println("thermostat off");
    lcd.print("Thermostat off");
    lcd.setCursor(0,3);
    lcd.print("Heater off");
    digitalWrite(relayPin8, LOW);
  }
  Serial.println("Loop");
}

