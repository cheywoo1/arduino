int waterPump = 3;
int monitoringInterval = 2000;
int activePumpingInterval = 1000;
int needsWaterCounter = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Monitoring Interval: " + String(monitoringInterval));
  Serial.println("Active Pumping Interval: " + String(activePumpingInterval));
  pinMode(waterPump, OUTPUT);
}
void loop() {
  delay(monitoringInterval);
  runPumpMonitor();
}
void runPumpMonitor() {
//this could be abstracted to multiple sensor/relay/pump tuples
//make the sensor/pump/relay combinations an array of structs
//loop through the array and pass as arguments to the routines 
  while (needsWater()) {
    openPump();
    delay(activePumpingInterval);
  }
  needsWaterCounter = 0;
  closePump();
}
boolean needsWater() {
  return (timeoutOK() && sensorSaysWater() && reservoirHasWater() && noOverflow());
}
boolean timeoutOK() {
  //keep track of how long it has been running and kill after too long
  return (needsWaterCounter++ < 3);
}
boolean noOverflow() {
  // add another sensor to the overflow dish, do not water if dish is wet
  return true;
}
boolean sensorSaysWater() {
  //determine threshhold level, return true if threshold exceeded by sensor reading
  return true;
}
boolean reservoirHasWater() {
  // add another sensor to the resrevoir, do not water if reservoir is dry
  return true;
}
void closePump() {
  Serial.println("Closing Pump");
  digitalWrite(waterPump, LOW);
}
void openPump() {
  Serial.println("Opening Pump");
  digitalWrite(waterPump, HIGH);
}
