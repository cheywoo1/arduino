bool logging = true;
bool runWithPumpOn = true;
int plantSensorPin = A0;
int overflowSensorPin = A1;
int reservoirSensorPin = A2;
int waterPumpPin = 3;
unsigned long monitoringInterval = 15000;
unsigned long moistureThreshold = 700;
unsigned long overflowThreshold = 800;
unsigned long reservoirThreshold = 1;
unsigned long maxWaterTime = 4000;
