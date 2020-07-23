#include <Stepper.h>

const int stepsPerRevolution = 2038; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int A5light, A4light, A3light, A2light;
int A5deg, A4deg, A3deg, A2deg;

void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(6);
  A5deg = 270;
  A4deg = 180;
  A3deg = 90;
  A2deg = 0;
}

int readData()
{
  A5light = analogRead(A5);
  A4light = analogRead(A4);
  A3light = analogRead(A3);
  A2light = analogRead(A2);
  Serial.println("A5: "+(String)A5light);
  Serial.println("A4: "+(String)A4light);
  Serial.println("A3: "+(String)A3light);
  Serial.println("A2: "+(String)A2light);
  Serial.println();
  
}

int getStepsToMove() 
{
  int maxLight = max(max(A5light, A4light), max(A3light, A2light));
  int minLight = min(min(A5light, A4light), min(A3light, A2light));

  int deg1, deg2;

  if (maxLight == A5light) {
    deg1 = A5deg;
  }
  else if (maxLight == A4light) {
    deg1 = A4deg;
  }
  else if (maxLight == A3light) {
    deg1 = A3deg;
  }
  else if (maxLight == A2light) {
    deg1 = A2deg;
  }
  
  if (minLight == A5light) {
    deg2 = A5deg;
  }
  else if (minLight == A4light) {
    deg2 = A4deg;
  }
  else if (minLight == A3light) {
    deg2 = A3deg;
  }
  else if (minLight == A2light) {
    deg2 = A2deg;
  }

  //deg1 = A2deg;
  //deg2 = A5deg;
  int steps = (int)((abs(deg1-deg2)/360.0)*stepsPerRevolution);
  return steps;
}

void loop()
{
  delay(5000);
  myStepper.step(1528);
  delay(5000);
  myStepper.step(1100);
  delay(5000);
  myStepper.step(600);
  delay(5000);
}
