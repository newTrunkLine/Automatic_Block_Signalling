// Wiring
const int leftSensorPin 	= A0;
const int rightSensorPin	= A1;

// Misc. variables
const int numSamples = 100;
const int senseThreshold = 200;
int leftSensorNomVal = 0;
int rightSensorNomVal = 0;

// Function declarations
int getNominalSensorVal(int pin);

void setup() {
  
  Serial.begin(9600);
  while(!Serial){ }

  leftSensorNomVal = getNominalSensorVal(leftSensorPin);
  rightSensorNomVal = getNominalSensorVal(rightSensorPin);
  Serial.print("Left sensor nominal value: "); Serial.println(leftSensorNomVal);
  Serial.print("Right sensor nominal value: "); Serial.println(rightSensorNomVal);
  delay(1000);
}

void loop() {
  bool leftSensorDetect = sensorDetect(leftSensorPin, leftSensorNomVal);
  bool rightSensorDetect = sensorDetect(rightSensorPin, rightSensorNomVal);
  Serial.print("Left sensor detect: "); Serial.print(leftSensorDetect ? "TRUE" : "FALSE"); Serial.print(", Right sensor detect: "); Serial.println(rightSensorDetect ? "TRUE" : "FALSE");

  delay(500);
}