int getNominalSensorVal(int pin){
  
  long nomSensorVal = 0;
  
  for(int i = 0; i < numSamples; i++){
    nomSensorVal += analogRead(pin);
    delay(1);
  }
  nomSensorVal /= numSamples;

  return static_cast<int>(nomSensorVal);
}

void enableLEDs(int state){
  
  switch(state){
    case green_green:
      digitalWrite(leftGreenLEDPin, HIGH);  digitalWrite(rightGreenLEDPin, HIGH);
      digitalWrite(leftYellowLEDPin, LOW);  digitalWrite(rightYellowLEDPin, LOW);
      digitalWrite(leftRedLEDPin, LOW);     digitalWrite(rightRedLEDPin, LOW);
      break;
    case green_yellow:
      digitalWrite(leftGreenLEDPin, HIGH);  digitalWrite(rightGreenLEDPin, LOW);
      digitalWrite(leftYellowLEDPin, LOW);  digitalWrite(rightYellowLEDPin, HIGH);
      digitalWrite(leftRedLEDPin, LOW);     digitalWrite(rightRedLEDPin, LOW);
      break;
    case yellow_green:
      digitalWrite(leftGreenLEDPin, LOW);   digitalWrite(rightGreenLEDPin, HIGH);
      digitalWrite(leftYellowLEDPin, HIGH); digitalWrite(rightYellowLEDPin, LOW);
      digitalWrite(leftRedLEDPin, LOW);     digitalWrite(rightRedLEDPin, LOW);
      break;
    case yellow_yellow:
      digitalWrite(leftGreenLEDPin, LOW);   digitalWrite(rightGreenLEDPin, LOW);
      digitalWrite(leftYellowLEDPin, HIGH); digitalWrite(rightYellowLEDPin, HIGH);
      digitalWrite(leftRedLEDPin, LOW);     digitalWrite(rightRedLEDPin, LOW);
      break;
    case red_red:
      digitalWrite(leftGreenLEDPin, LOW);   digitalWrite(rightGreenLEDPin, LOW);
      digitalWrite(leftYellowLEDPin, LOW);  digitalWrite(rightYellowLEDPin, LOW);
      digitalWrite(leftRedLEDPin, HIGH);    digitalWrite(rightRedLEDPin, HIGH);
      break;
    default:
      Serial.println("Error! Incorrect LED state!");
      digitalWrite(leftGreenLEDPin, LOW);   digitalWrite(rightGreenLEDPin, LOW);
      digitalWrite(leftYellowLEDPin, LOW);  digitalWrite(rightYellowLEDPin, LOW);
      digitalWrite(leftRedLEDPin, HIGH);    digitalWrite(rightRedLEDPin, HIGH);
      break;
  }
}
