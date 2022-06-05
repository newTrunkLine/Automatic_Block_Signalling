const int rightSensorPin    = A0;
const int leftSensorPin     = A1;
const int rightGreenLEDPin  = 2;
const int rightYellowLEDPin = 3;
const int rightRedLEDPin    = 4;
const int leftGreenLEDPin   = 5;
const int leftYellowLEDPin  = 6;
const int leftRedLEDPin     = 7;

const int numSamples = 100;
int leftSensorNomVal = 0;
int rightSensorNomVal = 0;

int getNominalSensorVal(int pin){
  long nomSensorVal = 0;
  
  for(int i = 0; i < numSamples; i++){
    nomSensorVal += analogRead(pin);
    delay(1);
  }
  nomSensorVal /= numSamples;

  return static_cast<int>(nomSensorVal);
}

void setup() {
  Serial.begin(9600);
  while(!Serial){ }

  leftSensorNomVal = getNominalSensorVal(leftSensorPin);
  rightSensorNomVal = getNominalSensorVal(rightSensorPin);
  Serial.print("Left sensor nominal value: "); Serial.println(leftSensorNomVal);
  Serial.print("Right sensor nominal value: "); Serial.println(rightSensorNomVal);
}

void loop() {
  // put your main code here, to run repeatedly:

}
