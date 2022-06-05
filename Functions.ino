int getNominalSensorVal(int pin){
  
  long nomSensorVal = 0;
  
  for(int i = 0; i < numSamples; i++){
    nomSensorVal += analogRead(pin);
    delay(1);
  }
  nomSensorVal /= numSamples;

  return static_cast<int>(nomSensorVal);
}

void enableGreenLEDs(int leftGreenValue, int rightGreenValue){
  digitalWrite(leftGreenLEDPin, leftGreenValue);
  digitalWrite(rightGreenLEDPin, rightGreenValue);
}

void enableYellowLEDs(int leftYellowValue, int rightYellowValue){
  digitalWrite(leftYellowLEDPin, leftYellowValue);
  digitalWrite(rightYellowLEDPin, rightYellowValue);
}

void enableRedLEDs(int leftRedValue, int rightRedValue){
  digitalWrite(leftRedLEDPin, leftRedValue);
  digitalWrite(rightRedLEDPin, rightRedValue);
}
