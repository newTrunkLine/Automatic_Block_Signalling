// Wiring
const int leftSensorPin     = A0;
const int rightSensorPin    = A1;
const int leftGreenLEDPin   = 7;
const int leftYellowLEDPin  = 6;
const int leftRedLEDPin     = 5;
const int rightGreenLEDPin  = 4;
const int rightYellowLEDPin = 3;
const int rightRedLEDPin    = 2;

// Misc. variables
const int numSamples = 100;
int leftSensorNomVal = 0;
int rightSensorNomVal = 0;

// Function declarations
int getNominalSensorVal(int pin);
void enableLEDs(int blockState);

enum blockState{
  green_green,
  green_yellow,
  yellow_green,
  yellow_yellow,
  red_red
}currentState;

void setup() {
  currentState = green_green;
  
  Serial.begin(9600);
  while(!Serial){ }

  leftSensorNomVal = getNominalSensorVal(leftSensorPin);
  rightSensorNomVal = getNominalSensorVal(rightSensorPin);
  Serial.print("Left sensor nominal value: "); Serial.println(leftSensorNomVal);
  Serial.print("Right sensor nominal value: "); Serial.println(rightSensorNomVal);
  delay(1000);
}

void loop() {
  int leftSensorVal = analogRead(leftSensorPin);
  int rightSensorVal = analogRead(rightSensorPin);

  Serial.print("Left sensor: "); Serial.print(leftSensorVal); Serial.print(", Right sensor: "); Serial.print(rightSensorVal);
  Serial.print(", Current state: "); Serial.println(currentState);

  enableLEDs(currentState);

  switch(currentState){
    case green_green:
      //
      break;
    case green_yellow:
      //
      break;
    case yellow_green:
      //
      break;
    case yellow_yellow:
      //
      break;
    case red_red:
      //
      break;
    default:
      //
      break;
  }
  
  delay(500);
}
