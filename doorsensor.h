
#define DOOR_SENSOR_PIN       12

portMUX_TYPE DSmux = portMUX_INITIALIZER_UNLOCKED;

class DoorSensor {
  private:
      byte _sensorPin;
      volatile byte _sensorValue;
      volatile byte _sensorChanged;
  
  public:
      DoorSensor(const int sensorPin); //done
      byte isDoorOpen(void);                //done
      void updateDoorState(void);              //done
      byte isDoorStateChanged(void);
};

/**
 * intialize pins and variables
 */
DoorSensor::DoorSensor(const int sensorPin)
{
  pinMode(sensorPin, INPUT_PULLUP);
  this->_sensorPin    =  sensorPin;
  this->_sensorValue   =  digitalRead(this->_sensorPin);
  this->_sensorChanged  =  1;
}

/*
 * return the actual pin state of door sensor
 * user called
 */
byte DoorSensor::isDoorOpen(void) { return this->_sensorValue; }

/**
 * updates the door sensor value
 * called from inteuupt, keep short
 */
void DoorSensor::updateDoorState(void) 
{ 
  this->_sensorValue = digitalRead(this->_sensorPin); 
  this->_sensorChanged = 1;
}

/**
 * return if door is opened or closed
 * user called
 */
byte DoorSensor::isDoorStateChanged(void) 
{
  if(this->_sensorChanged) 
  {
    this->_sensorChanged = 0;
    return 1;
  }
  else return 0;
}

/*****************************************
 ************ Interrupt & Global Code***
 *****************************************/



