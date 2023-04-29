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

bool blockDetect(int pin){
  if(digitalRead(pin) == HIGH){
    return true;
  }else{
    return false;
  }
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

void enableTX(int state){
  switch(state){
    case green_green:
      digitalWrite(leftBlockTXPin, LOW);
      digitalWrite(rightBlockTXPin, LOW);
      break;
    case green_yellow:
      digitalWrite(leftBlockTXPin, LOW);
      digitalWrite(rightBlockTXPin, LOW);
      break;
    case yellow_green:
      digitalWrite(leftBlockTXPin, LOW);
      digitalWrite(rightBlockTXPin, LOW);
      break;
    case yellow_yellow:
      //digitalWrite(leftBlockTXPin, LOW);
      //digitalWrite(rightBlockTXPin, LOW);
      break;
    case red_red:
      digitalWrite(leftBlockTXPin, HIGH);
      digitalWrite(rightBlockTXPin, HIGH);
      break;
    default:
      digitalWrite(leftBlockTXPin, HIGH);
      digitalWrite(rightBlockTXPin, HIGH);
      break;
  }
}

void signalGreenGreen(bool leftBlock, bool rightBlock, bool leftSensor, bool rightSensor){
  if(leftBlock && !rightBlock && !leftSensor && !rightSensor){
    currentState = green_yellow;
  }else if(!leftBlock && rightBlock && !leftSensor && !rightSensor){
    currentState = yellow_green;
  }//else if(leftBlock && 
}
