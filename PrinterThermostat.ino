// Initialie variable for relay
int relay8 = 8;

//

void setup()
{
  //Assign variable for relay
  pinMode(relay8, OUTPUT); //sets pin
  digitalWrite(relay8, HIGH); //Starts disengaged
}

void loop()
{
  //Relay test, change state every 2 seconds
  relayOn(relay8);
  delay(2000);
  relayOff(relay8);
  delay(2000);
}

//Setup functions to turn relay on and off
int relayOn (int relayNumber) {digitalWrite(relayNumber, LOW);}
int relayOff (int relayNumber) {digitalWrite(relayNumber, HIGH);}
