#include "settings.h"
unsigned long previousMillis = 0;       // will store last time through the monitor
unsigned long previousWaterMillis = 0;  // will store last time starting water
unsigned long startLoopTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(waterPumpPin, OUTPUT);
  logInitialization();
}
void loop() {
  startLoopTime = millis();
  if (startLoopTime - previousMillis >= monitoringInterval) {
    previousMillis = startLoopTime;
    logSensorValues();
    while (shouldWater()) {
      log("Watering");
      openPump();
      logSensorValues();
    }
    closePump();
    log("Waiting for " + String(monitoringInterval / 1000) + " seconds");
  }
}
boolean shouldWater() {
  return (hasNotTimedOut() && plantSensorReadsDry() && reservoirHasWater() && hasNoOverflow());
}
boolean hasNotTimedOut() {
  //Return true if max water time not exceeded
  if (((millis() - startLoopTime) >= maxWaterTime)) {
    log("Timed out after " + String(maxWaterTime / 1000) + " seconds");
  };
  return ((millis() - startLoopTime) < maxWaterTime);
}
boolean plantSensorReadsDry() {
  //Return true if moisture level is below threshold
  return (analogRead(plantSensorPin) > moistureThreshold);
}
boolean reservoirHasWater() {
  //STUB Return true if reservoir sensor is wet
  return true;
  return (analogRead(reservoirSensorPin) < reservoirThreshold);
}
boolean hasNoOverflow() {
  // Return true if overflow sensor is dry
  return (analogRead(overflowSensorPin) > overflowThreshold);
}
void closePump() {
  log("Closing Pump");
  digitalWrite(waterPumpPin, LOW);
}
void openPump() {
  log("Opening Pump");
  if (runWithPumpOn) {
    digitalWrite(waterPumpPin, HIGH);
  }
}
void logSensorValues() {
  log("Plant Sensor:" + String(analogRead(plantSensorPin)) + "(" + String(moistureThreshold) + ")");
  log("Overflow Sensor:" + String(analogRead(overflowSensorPin)) + "(" + String(overflowThreshold) + ")");
  log("Reservoir Sensor:" + String(analogRead(reservoirSensorPin)) + "(" + String(reservoirThreshold) + ")");
}
void logInitialization() {
  log("Settings");
  log("Monitoring Interval: " + String(monitoringInterval / 1000) + " seconds");
  log("Max Continuous water time: >= " + String(maxWaterTime / 1000) + " seconds");
  log("Soil Moisture Threshold: > " + String(moistureThreshold));
  log("Overflow Threshold: > " + String(overflowThreshold));
  log("Reservoir Threshold: " + String(reservoirThreshold));
  log("Logging: " + (String((logging ? "true" : "false"))));
  log("Run pump: " + (String((runWithPumpOn ? "true" : "false"))));
}
void log(String message) {
  if (logging) {
    Serial.println(message);
  }
}
