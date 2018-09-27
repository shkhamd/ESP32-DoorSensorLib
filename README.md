# ESP32-DoorSensorLib
An easy to setup library for ESP32 and door sensor with sensor interrupt input

_**DoorSensor**_ class has three private variables manipulated by 4 public methods. 

_**DoorSensor(const int sensorPin)**_ : Class constructor, initializes a door sensor pin as INPUT with Internal PULLUP enabled. 
_**byte isDoorOpen(void)**_ : as the name goes, returns true if the door is open, else false. Called by USER code. 
_**void updateDoorState(void)**_ : if the door state (OPEN, CLOSED). SHOULD BE CALLED inside the door sensor interrupt handler. 
_**byte isDoorStateChanged(void)**_ : asserts _true_ if a sensor interrupts occur and the door state has been changed. Called by USER Code. 

## How to use the library: 

if your _example_ is your sketch file name then it has the following directory structure. 
  _./example/example.ino_       
  
Now place the _doorsensor.h_ file according to the following: 
  ./example/doorsensor.h
  
In your arduino code, use:
```
#include "doorsensor.h"
```

Then create a _DoorSensor_ instance e.g. _DS_ like this: 
```
DoorSensor DS(DOOR_SENSOR_PIN);
```

Then add the sensor interrupt code: 

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
