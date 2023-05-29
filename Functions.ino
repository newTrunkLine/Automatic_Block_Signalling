int getNominalSensorVal(int pin){
 
  long nomSensorVal = 0;
 
  for(int i = 0; i < numSamples; i++){
	nomSensorVal += analogRead(pin);
	delay(1);
  }
  nomSensorVal /= numSamples;

  return static_cast<int>(nomSensorVal);
}

bool sensorDetect(int pin, int nomVal){
  return ((nomVal - analogRead(pin)) > senseThreshold);
}
