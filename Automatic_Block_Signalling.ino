// Wiring
const int rightSensorPin	  = A0;
const int leftSensorPin 	  = A5;

const int leftGreenLEDPin   = 4;
const int leftYellowLEDPin  = 3;
const int leftRedLEDPin     = 2;
const int rightGreenLEDPin  = 11;
const int rightYellowLEDPin = 12;
const int rightRedLEDPin    = 13;

// Misc. variables
const int numSamples = 100;
const int senseThreshold = 250;
int leftSensorNomVal = 0;
int rightSensorNomVal = 0;

enum signalState{
  stateGreenGreen,
  stateYellowGreen,
  stateGreenYellow,
  stateYellowYellow,
  stateRedRed,
}currentState;

void setup() {
  
  Serial.begin(9600);
  while(!Serial){ }

  pinMode(leftGreenLEDPin, OUTPUT);
  pinMode(leftYellowLEDPin, OUTPUT);
  pinMode(leftRedLEDPin, OUTPUT);
  pinMode(rightGreenLEDPin, OUTPUT);
  pinMode(rightYellowLEDPin, OUTPUT);
  pinMode(rightRedLEDPin, OUTPUT);

  currentState = stateGreenGreen;

  leftSensorNomVal = getNominalSensorVal(leftSensorPin);
  rightSensorNomVal = getNominalSensorVal(rightSensorPin);

  Serial.print("Left sensor nominal value: "); Serial.println(leftSensorNomVal);
  Serial.print("Right sensor nominal value: "); Serial.println(rightSensorNomVal);
  delay(1000);
}

void loop() {
  /*
  int leftRaw = getSensorRawVal(leftSensorPin);
  int rightRaw = getSensorRawVal(rightSensorPin);
  
  int leftSensorVal = getSensorVal(leftSensorPin, leftSensorNomVal);
  int rightSensorVal = getSensorVal(rightSensorPin, rightSensorNomVal);
  
  //Serial.print("Left raw: "); Serial.print(leftRaw); Serial.print(", Right raw: "); Serial.print(rightRaw); 
  Serial.print(", Left: "); Serial.print(leftSensorVal); Serial.print(", Right: "); Serial.print(rightSensorVal);
  */

  bool leftSensorTriggered = isSensorTriggered(leftSensorPin, leftSensorNomVal);
  bool rightSensorTriggered = isSensorTriggered(rightSensorPin, rightSensorNomVal);

  Serial.print("Left sensor: "); Serial.print(leftSensorTriggered); Serial.print(", Right sensor: "); Serial.print(rightSensorTriggered); Serial.print("Current state: "); Serial.println(currentState);
  //Serial.print("Left sensor detect: "); Serial.print(leftSensorDetect ? "TRUE" : "FALSE"); Serial.print(", Right sensor detect: "); Serial.println(rightSensorDetect ? "TRUE" : "FALSE");

  switch(currentState){
    case stateGreenGreen:
    signalGreenGreen();
    break;

    case stateYellowGreen:
    break;

    case stateGreenYellow:
    break;

    case stateYellowYellow:
    break;

    case stateRedRed:
    break;
  }

  enableLEDs(currentState);

  delay(500);
}

