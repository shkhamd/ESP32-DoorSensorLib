#include "doorsensor.h"

#define SERIAL_BAUD       115200

/**====================================
 * Door sensor and interrupt
 */
DoorSensor DS(DOOR_SENSOR_PIN);
void IRAM_ATTR DoorSensorInterrupt() 
{
  portENTER_CRITICAL_ISR(&DSmux);
  DS.updateDoorState();
  portEXIT_CRITICAL_ISR(&DSmux);
}
//====================================



void setup() 
{
  Serial.begin(SERIAL_BAUD);
  attachInterrupt(digitalPinToInterrupt(DOOR_SENSOR_PIN), DoorSensorInterrupt, CHANGE);
}
 
void loop() 
{
   portENTER_CRITICAL(&DSmux);
   if(DS.isDoorStateChanged())
     Serial.println( DS.isDoorOpen() ? "DOOR OPEN" : "DOOR CLOSED" );
   portEXIT_CRITICAL(&DSmux);
   delay(1000);
}
