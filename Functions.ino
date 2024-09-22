int getNominalSensorVal(int pin){
 
  long nomSensorVal = 0;

  // Calculate average value for nominal sensor output (untriggered)
  for(int i = 0; i < numSamples; i++){
	  nomSensorVal += analogRead(pin);
	  delay(1);
  }
  nomSensorVal /= numSamples;

  return static_cast<int>(nomSensorVal);
}

bool isSensorTriggered(int pin, int nomVal){

  // Return true if the absolute difference between the current reading and the nominal value is greater than the threshold
  return (abs(nomVal - analogRead(pin)) > senseThreshold);
}

bool isBlockOccupied(int pin){

  // Return true if comms pin to adjacent block is HIGH
  if(digitalRead(pin) == HIGH){
    return true;
  }else{
    return false;
  }
}

void enableTX(int state){

  // Send HIGH/LOW signals to adjacent blocks as necessary
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
  	digitalWrite(leftBlockTXPin, LOW);
  	digitalWrite(rightBlockTXPin, LOW);
  	break;

	case stateYellowYellow:
    if(!needExitingCheck){
      digitalWrite(leftBlockTXPin, LOW);
  	  digitalWrite(rightBlockTXPin, LOW);

    }else{
      digitalWrite(leftBlockTXPin, HIGH);
  	  digitalWrite(rightBlockTXPin, HIGH);
    }
  	break;

	case stateRedRed:
  	digitalWrite(leftBlockTXPin, HIGH);
  	digitalWrite(rightBlockTXPin, HIGH);
  	break;

	default:
    Serial.println("Error! Incorrect TX state!");
  	digitalWrite(leftBlockTXPin, HIGH);
  	digitalWrite(rightBlockTXPin, HIGH);
  	break;
  }
}

void enableLEDs(int state){

  // Enable entry signals as necessary
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

  // Check which sensors are triggered, status of adjacent blocks, switch to relevant state
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
  }
}

void signalYellowGreen(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc){
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
    
  }else if(!leftBlockOcc && !rightBlockOcc){
    currentState = stateGreenGreen;
  }
}

void signalYellowYellow(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc, unsigned long currentMillis){
  if(!needExitingCheck){
    // If YY state triggered only by adjacent blocks
    if(leftSensorTrig){
      entryFromLeft = true;
      currentState = stateRedRed;

    }else if(rightSensorTrig){
      entryFromLeft = false;
      currentState = stateRedRed;

    }else if(leftBlockOcc && !rightBlockOcc){
      currentState = stateGreenYellow;

    }else if(rightBlockOcc && !leftBlockOcc){
      currentState = stateYellowGreen;

    }else if(!leftBlockOcc && !rightBlockOcc){
      currentState = stateGreenGreen;
    }
  }else{
    if((currentMillis - yellowStartMillis) <= yellowInterval){

      // For 5 seconds, check both sensors. If either is triggered, extend YY state by another 5 seconds
      if(leftSensorTrig || rightSensorTrig){
        yellowStartMillis = millis();
      }
    }else{
      if(!leftSensorTrig && !rightSensorTrig){

        // If after 5 seconds neither sensor is triggered AND adjacent blocks are clear, return to GG state
        if(leftBlockOcc && rightBlockOcc){
          needExitingCheck = false;
          currentState = stateYellowYellow;

        }else if(leftBlockOcc && !rightBlockOcc){
          currentState = stateGreenYellow;
          
        }else if(rightBlockOcc && !leftBlockOcc){
          currentState = stateYellowGreen;

        }else{
          currentState = stateGreenGreen;
          }
      } 
    }
  }
}

void signalRedRed(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc){
  needExitingCheck = true;

  if(entryFromLeft){
    if(!leftSensorTrig && rightSensorTrig){
      // If train entered from left and is now exiting, start timer and switch to YY
      yellowStartMillis = millis();
      currentState = stateYellowYellow;
    }
  }else{
    if(leftSensorTrig && !rightSensorTrig){
      yellowStartMillis = millis();
      currentState = stateYellowYellow;
    }
  }
}

// Debug Functions

int getSensorRawVal(int pin){
  return analogRead(pin);
}

int getSensorVal(int pin, int nomVal){
  return abs(nomVal - analogRead(pin));
}