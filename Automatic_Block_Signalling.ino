#define DEBUG

// Wiring
const int rightSensorPin	      = A0;
const int leftSensorPin 	      = A5;

const int leftBlockRXPin        = 3;
const int leftBlockTXPin        = 2;
const int rightBlockRXPin       = 12;
const int rightBlockTXPin       = 13;

const int leftGreenLEDPin       = 7;
const int leftYellowLEDPin      = 6;
const int leftRedLEDPin         = 5;
const int rightGreenLEDPin      = 8;
const int rightYellowLEDPin     = 9;
const int rightRedLEDPin        = 10;

// Misc. variables
const int numSamples            = 1000;
const int senseThreshold        = 400;
const int yellowInterval        = 1500;
int leftSensorNomVal            = 0;
int rightSensorNomVal           = 0;
unsigned long yellowStartMillis = 0;
bool entryFromLeft              = false;
bool needExitingCheck           = false;

// Forward declarations
int getNominalSensorVal(int pin);
bool isSensorTriggered(int pin, int nomVal);
bool isBlockOccupied(int pin);
void enableTX(int state);
void enableLEDs(int state);
void signalGreenGreen(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc);
void signalGreenYellow(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc);
void signalYellowGreen(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc);
void signalYellowYellow(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc, unsigned long currentMillis);
void signalRedRed(bool leftSensorTrig, bool rightSensorTrig, bool leftBlockOcc, bool rightBlockOcc);
int getSensorRawVal(int pin);
int getSensorVal(int pin, int nomVal);

enum signalState{
  stateGreenGreen,
  stateGreenYellow,
  stateYellowGreen,
  stateYellowYellow,
  stateRedRed,
}currentState;

void setup() {
  
  Serial.begin(9600);
  while(!Serial){ }

  Serial.println();

  pinMode(leftGreenLEDPin, OUTPUT);
  pinMode(leftYellowLEDPin, OUTPUT);
  pinMode(leftRedLEDPin, OUTPUT);
  pinMode(rightGreenLEDPin, OUTPUT);
  pinMode(rightYellowLEDPin, OUTPUT);
  pinMode(rightRedLEDPin, OUTPUT);

  pinMode(leftBlockRXPin, INPUT);
  pinMode(leftBlockTXPin, OUTPUT);
  pinMode(rightBlockRXPin, INPUT);
  pinMode(rightBlockTXPin, OUTPUT);

  currentState = stateGreenGreen;

  leftSensorNomVal = getNominalSensorVal(leftSensorPin);
  rightSensorNomVal = getNominalSensorVal(rightSensorPin);

  Serial.print("Left sensor nominal value: "); Serial.println(leftSensorNomVal);
  Serial.print("Right sensor nominal value: "); Serial.println(rightSensorNomVal);
  Serial.println();
  delay(1000);
}

void loop() {
  #ifdef DEBUG
  int leftRaw = getSensorRawVal(leftSensorPin);
  int rightRaw = getSensorRawVal(rightSensorPin);
  
  int leftSensorVal = getSensorVal(leftSensorPin, leftSensorNomVal);
  int rightSensorVal = getSensorVal(rightSensorPin, rightSensorNomVal);
  
  Serial.print("Left raw: "); Serial.print(leftRaw); Serial.print("\t Right raw: "); Serial.print(rightRaw); 
  Serial.print("\t Left: "); Serial.print(leftSensorVal); Serial.print("\t Right: "); Serial.print(rightSensorVal); Serial.print("\t");
  #endif

  bool leftSensorTriggered = isSensorTriggered(leftSensorPin, leftSensorNomVal);
  bool rightSensorTriggered = isSensorTriggered(rightSensorPin, rightSensorNomVal);

  bool leftBlockOccupied = isBlockOccupied(leftBlockRXPin);
  bool rightBlockOccupied = isBlockOccupied(rightBlockRXPin);

  const char* stateStr[] = {"GG", "GY", "YG", "YY", "RR"};
  unsigned long currentMillis = millis();

  //Serial.print("Left sensor: "); Serial.print(leftSensorTriggered); Serial.print("\t Right sensor: "); Serial.print(rightSensorTriggered); Serial.print("\t");
  Serial.print("Left block: "); Serial.print(leftBlockOccupied); Serial.print("\t Right block: "); Serial.print(rightBlockOccupied);
  Serial.print("\t Current state: "); Serial.print(stateStr[currentState]);
  Serial.print("\t Current millis: "); Serial.print(currentMillis); Serial.print("\t Yellow start millis: "); Serial.print(yellowStartMillis);
  Serial.print("\t Diff: "); Serial.println(currentMillis - yellowStartMillis);

  enableLEDs(currentState);
  enableTX(currentState);

  switch(currentState){
    case stateGreenGreen:
      signalGreenGreen(leftSensorTriggered, rightSensorTriggered, leftBlockOccupied, rightBlockOccupied);
    break;

    case stateGreenYellow:
      signalGreenYellow(leftSensorTriggered, rightSensorTriggered, leftBlockOccupied, rightBlockOccupied);
    break;

    case stateYellowGreen:
      signalYellowGreen(leftSensorTriggered, rightSensorTriggered, leftBlockOccupied, rightBlockOccupied);
    break;

    case stateYellowYellow:
      signalYellowYellow(leftSensorTriggered, rightSensorTriggered, leftBlockOccupied, rightBlockOccupied, currentMillis);
    break;

    case stateRedRed:
      signalRedRed(leftSensorTriggered, rightSensorTriggered, leftBlockOccupied, rightBlockOccupied);
    break;
  }
  delay(250);
}

