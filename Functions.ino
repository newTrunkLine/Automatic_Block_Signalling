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

bool isBlockOccupied(int pin){
  if(digitalRead(pin) == HIGH){
    return true;
  }else{
    return false;
  }
}

void enableTX(int state){
  switch(state){
	case stateGreenGreen:
  	digitalWrite(leftBlockTXPin, LOW);
  	digitalWrite(rightBlockTXPin, LOW);
  	break;
  case stateGreenYellow:
  	digitalWrite(leftBlockTXPin, LOW);
  	digitalWrite(rightBlockTXPin, LOW);
  	break;
	case stateYellowGreen:	
  	//digitalWrite(leftBlockTXPin, LOW);
  	//digitalWrite(rightBlockTXPin, LOW);
  	break;
	case stateYellowYellow:
  	//digitalWrite(leftBlockTXPin, LOW);
  	//digitalWrite(rightBlockTXPin, LOW);
  	break;
	case stateRedRed:
  	//digitalWrite(leftBlockTXPin, HIGH);
  	//digitalWrite(rightBlockTXPin, HIGH);
  	break;
	default:
  	//digitalWrite(leftBlockTXPin, HIGH);
  	//digitalWrite(rightBlockTXPin, HIGH);
  	break;
  }
}

void enableLEDs(int state){
  switch(state){
    case stateGreenGreen:
      digitalWrite(leftGreenLEDPin, HIGH);    digitalWrite(rightGreenLEDPin, HIGH);
  	  digitalWrite(leftYellowLEDPin, LOW);    digitalWrite(rightYellowLEDPin, LOW);
  	  digitalWrite(leftRedLEDPin, LOW); 	    digitalWrite(rightRedLEDPin, LOW);
    break;

    case stateGreenYellow:
      digitalWrite(leftGreenLEDPin, HIGH);    digitalWrite(rightGreenLEDPin, LOW);
  	  digitalWrite(leftYellowLEDPin, LOW);    digitalWrite(rightYellowLEDPin, HIGH);
  	  digitalWrite(leftRedLEDPin, LOW); 	    digitalWrite(rightRedLEDPin, LOW);
    break;

    case stateYellowGreen:
      digitalWrite(leftGreenLEDPin, LOW);     digitalWrite(rightGreenLEDPin, HIGH);
  	  digitalWrite(leftYellowLEDPin, HIGH);   digitalWrite(rightYellowLEDPin, LOW);
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

    default:
      Serial.println("Error! Incorrect LED state!");
  	  digitalWrite(leftGreenLEDPin, LOW);   digitalWrite(rightGreenLEDPin, LOW);
  	  digitalWrite(leftYellowLEDPin, LOW);  digitalWrite(rightYellowLEDPin, LOW);
  	  digitalWrite(leftRedLEDPin, HIGH);	digitalWrite(rightRedLEDPin, HIGH);
  	break;
  }
}

void signalGreenGreen(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc){
  if(leftSensorTrig){
    entryFromLeft = true;
    currentState = stateRedRed;
  }else if(rightSensorTrig){
    entryFromLeft = false;
    currentState = stateRedRed;
  }else if(leftBlockOcc && rightBlockOcc){
    needExitingCheck = false;
    currentState = stateYellowYellow;
  }else if(leftBlockOcc && !rightBlockOcc){
    currentState = stateGreenYellow;
  }else if(rightBlockOcc && !leftBlockOcc){
    currentState = stateYellowGreen;
  }else{
    Serial.println("Error! Unknown inputs for state GG");
  }
}

void signalGreenYellow(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc){
  if(leftSensorTrig){
    entryFromLeft = true;
    currentState = stateRedRed;
  }else if(rightSensorTrig){
    entryFromLeft = false;
    currentState = stateRedRed;
  }else if(leftBlockOcc && rightBlockOcc){
    needExitingCheck = false;
    currentState = stateYellowYellow;
  }else if(rightBlockOcc && !leftBlockOcc){
    currentState = stateYellowGreen;
  }else if(!leftBlockOcc && !rightBlockOcc){
    currentState = stateGreenGreen;
  }else{
    Serial.println("Error! Unknown inputs for state GY");
  }
}

// Debug Functions

int getSensorRawVal(int pin){
  return analogRead(pin);
}

int getSensorVal(int pin, int nomVal){
  return abs(nomVal - analogRead(pin));
}