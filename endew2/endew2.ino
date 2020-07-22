#include <Stepper.h>

const int stepsPerRevolution = 2038; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int A3light, A2light, A1light, A0light;
int A3deg, A2deg, A1deg, A0deg;

void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(6);
  A3deg = 270;
  A2deg = 180;
  A1deg = 90;
  A0deg = 0;
}

int readData()
{
  A3light = analogRead(A3);
  A2light = analogRead(A2);
  A1light = analogRead(A1);
  A0light = analogRead(A0);
  Serial.println("A3: "+(String)A3light);
  Serial.println("A2: "+(String)A2light);
  Serial.println("A1: "+(String)A1light);
  Serial.println("A0: "+(String)A0light);
  Serial.println();
  
}

int getStepsToMove() 
{
  int maxLight = max(max(A3light, A2light), max(A1light, A0light));
  int minLight = min(min(A3light, A2light), min(A1light, A0light));

  int deg1, deg2;

  if (maxLight == A3light) {
    deg1 = A3deg;
  }
  else if (maxLight == A2light) {
    deg1 = A2deg;
  }
  else if (maxLight == A1light) {
    deg1 = A1deg;
  }
  else if (maxLight == A0light) {
    deg1 = A0deg;
  }
  
  if (minLight == A3light) {
    deg2 = A3deg;
  }
  else if (minLight == A2light) {
    deg2 = A2deg;
  }
  else if (minLight == A1light) {
    deg2 = A1deg;
  }
  else if (minLight == A0light) {
    deg2 = A0deg;
  }

  //deg1 = A0deg;
  //deg2 = A3deg;
  int steps = (int)((abs(deg1-deg2)/360.0)*stepsPerRevolution);
  return steps;
}

void loop()
{
  readData();
  int steps = getStepsToMove();
  myStepper.step(steps);
  delay(5000);
}
