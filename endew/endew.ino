#include <Stepper.h>

const int stepsPerRevolution = 2038; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int A5light, A4light, A3light, A2light;
int A5deg, A4deg, A3deg, A2deg;

void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(6);
  A5deg = 270; //org yelow
  A4deg = 180; //green blue
  A3deg = 90; //blck brown
  A2deg = 0; //white red
}

int readData()
{
  A5light = analogRead(A5);
  A4light = analogRead(A4);
  Serial.println(A5light);
  Serial.println(A4light);
  
  A3light = analogRead(A3);
  A2light = analogRead(A2);
  Serial.println(A3light);
  Serial.println(A2light);
}

int getStepsToMove() 
{
  int maxLight1 = max(A5light, A4light);
  int minLight1 = min(A5light, A4light);
  int maxLight2 = max(A3light, A2light);
  int minLight2 = min(A3light, A2light);

  int finalMax = max (maxLight1, maxLight2);
  int finalMin = min (minLight1, minLight2);
  int deg1, deg2; 
  
  if (finalMax == A5light) {
    deg1 = A5deg;
    if (finalMin == A4light) {
      deg2 = A4deg;
    }
    if(finalMin == A3light) {
      deg2 = A3deg;
    }
    if(finalMin == A2light) {
      deg2 = A2deg;
    }
  }
  
   if (finalMax == A4light) {
    deg1 = A4deg;
    if (finalMin == A5light) {
      deg2 = A5deg;
    }
    if(finalMin == A3light) {
      deg2 = A3deg;
    }
    if(finalMin == A2light) {
      deg2 = A2deg;
    }
  }
  
   if (finalMax == A3light) {
    deg1 = A3deg;
    if (finalMin == A4light) {
      deg2 = A4deg;
    }
    if(finalMin == A5light) {
      deg2 = A5deg;
    }
    if(finalMin == A2light) {
      deg2 = A2deg;
    }
  }

   if (finalMax == A2light) {
    deg1 = A2deg;
    if (finalMin == A4light) {
      deg2 = A4deg;
    }
    if(finalMin == A3light) {
      deg2 = A3deg;
    }
    if(finalMin == A5light) {
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