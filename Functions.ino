int getNominalSensorVal(int pin){
 
  long nomSensorVal = 0;
 
  for(int i = 0; i < numSamples; i++){
	nomSensorVal += analogRead(pin);
	delay(1);
  }
  nomSensorVal /= numSamples;

  return static_cast<int>(nomSensorVal);
}

bool isSensorTriggered(int pin, int nomVal){
  return (abs(nomVal - analogRead(pin)) > senseThreshold);
}

void signalGreenGreen(){
}

void enableLEDs(int state){
  switch(state){
    case stateGreenGreen:
    digitalWrite(leftGreenLEDPin, HIGH);    digitalWrite(rightGreenLEDPin, HIGH);
  	digitalWrite(leftYellowLEDPin, LOW);    digitalWrite(rightYellowLEDPin, LOW);
  	digitalWrite(leftRedLEDPin, LOW); 	    digitalWrite(rightRedLEDPin, LOW);
    break;

    case stateYellowGreen:
    digitalWrite(leftGreenLEDPin, LOW);     digitalWrite(rightGreenLEDPin, HIGH);
  	digitalWrite(leftYellowLEDPin, HIGH);   digitalWrite(rightYellowLEDPin, LOW);
  	digitalWrite(leftRedLEDPin, LOW); 	    digitalWrite(rightRedLEDPin, LOW);
    break;

    case stateGreenYellow:
    digitalWrite(leftGreenLEDPin, HIGH);    digitalWrite(rightGreenLEDPin, LOW);
  	digitalWrite(leftYellowLEDPin, LOW);    digitalWrite(rightYellowLEDPin, HIGH);
  	digitalWrite(leftRedLEDPin, LOW); 	    digitalWrite(rightRedLEDPin, LOW);
    break;

    case stateYellowYellow:
    digitalWrite(leftGreenLEDPin, LOW);     digitalWrite(rightGreenLEDPin, LOW);
  	digitalWrite(leftYellowLEDPin, HIGH);   digitalWrite(rightYellowLEDPin, HIGH);
  	digitalWrite(leftRedLEDPin, LOW); 	    digitalWrite(rightRedLEDPin, LOW);
    break;

    case stateRedRed:
    digitalWrite(leftGreenLEDPin, LOW);     digitalWrite(rightGreenLEDPin, LOW);
  	digitalWrite(leftYellowLEDPin, LOW);    digitalWrite(rightYellowLEDPin, LOW);
  	digitalWrite(leftRedLEDPin, HIGH); 	    digitalWrite(rightRedLEDPin, HIGH);
    break;
  }
}

// Debug Functions

int getSensorRawVal(int pin){
  return analogRead(pin);
}

int getSensorVal(int pin, int nomVal){
  return abs(nomVal - analogRead(pin));
}