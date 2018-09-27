# ESP32-DoorSensorLib
An easy to setup library for ESP32 and door sensor with sensor interrupt input

_**DoorSensor**_ class has three private variables manipulated by 4 public methods. 

_**DoorSensor(const int sensorPin)**_ : Class constructor, initializes a door sensor pin as INPUT with Internal PULLUP enabled.
 
_**byte isDoorOpen(void)**_ : as the name goes, returns true if the door is open, else false. Called by USER code. 

_**void updateDoorState(void)**_ : if the door state (OPEN, CLOSED). SHOULD BE CALLED inside the door sensor interrupt handler. 

_**byte isDoorStateChanged(void)**_ : asserts _true_ if a sensor interrupts occur and the door state has been changed. Called by USER Code. 


## How to use the library: 

if _example_ is your sketch file name then it has the following directory structure. 
  _./example/example.ino_       
  
Now place the _doorsensor.h_ file according to the following: 
  ./example/doorsensor.h
  
In your arduino code, use:
```
#include "doorsensor.h"
```

Then create a _DoorSensor_ instance e.g. _DS_ like this in **global scope**: 
```
DoorSensor DS(DOOR_SENSOR_PIN);
```

Then add the sensor interrupt code in **global scope**: 

```
void IRAM_ATTR DoorSensorInterrupt() 
{
  portENTER_CRITICAL_ISR(&DSmux);
  //here add the respective sensor instanc's update code
  // <doorsensor object>.updateDoorState()
  DS.updateDoorState();
  portEXIT_CRITICAL_ISR(&DSmux);
}
```

Now inside setup, attach the interrupt for the sensor input pin like this; 

```
void setup() 
{
  attachInterrupt(digitalPinToInterrupt(DOOR_SENSOR_PIN), DoorSensorInterrupt, CHANGE);
}
```

Now inside your loop or process (in RTOS environment), use these two methods:
```
<DoorSensor>.isDoorStateChanged()
<DoorSensor>.isDoorOpen()
``` 
e.g. 

```
void loop() 
{
   portENTER_CRITICAL(&DSmux); //used for RTOS compatibility
   if(DS.isDoorStateChanged())
     Serial.println( DS.isDoorOpen() ? "DOOR OPEN" : "DOOR CLOSED" );
   portEXIT_CRITICAL(&DSmux); //used for RTOS compatibility, can be ignored on single process microcontrollers, e.g. atMega328 based micros
   
   delay(1000); // delay represents other codes taking a long time before returning to the above block
}
```


Complete example code: 

```
#include "doorsensor.h"

DoorSensor DS(DOOR_SENSOR_PIN);

void IRAM_ATTR DoorSensorInterrupt() 
{
  portENTER_CRITICAL_ISR(&DSmux);
  DS.updateDoorState();
  portEXIT_CRITICAL_ISR(&DSmux);
}

void setup() 
{
  Serial.begin(115200);
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
 
```
