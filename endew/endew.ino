#include <Stepper.h>

const int stepsPerRevolution = 2038; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int A5light, A4light, A3light, A2light;
int A5deg, A4deg, A3deg, A2deg;

void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(6);
  A5deg = 360;
  A4deg = 180;
  //A3deg = 90;
  //A2deg = 0;
}

int readData()
{
  A5light = analogRead(A5);
  A4light = analogRead(A4);
  Serial.println(A5light);
  Serial.println(A4light);
  
  //A3 = analogRead(A3);
  //A2 = analogRead(A2);
}

int getStepsToMove() 
{
  int maxLight = max(A5light, A4light);
  int minLight = min(A5light, A4light);
  int deg1, deg2;
  
  if (maxLight == A5light) {
    deg1 = A5deg;
    if (minLight == A4light) {
      deg2 = A4deg;
    }
  }
  if (maxLight == A4light) {
    deg1 = A4deg;
    if (minLight == A5light) {
      deg2 = A5deg;
    }
  }
  int steps = map(abs(deg1-deg2), 0, 360, 0, stepsPerRevolution);
  return steps;
}

void loop()
{
  readData();
  int steps = getStepsToMove();
  myStepper.step(steps);
  delay(10000);
}
