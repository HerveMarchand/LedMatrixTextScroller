#include "matrixTextScroller.h"
 
int pinCLK = 10;
int pinCS  = 14;
int pinDIN = 12;

MatrixTextScrollerClass myTestMatrix = MatrixTextScrollerClass(pinCLK, pinCS, pinDIN);

void setup()
{

  myTestMatrix.setTextToDisplayWithLoopNumber("This is my text");
  myTestMatrix.setTextUpdatePeriod(35);
  myTestMatrix.setIntensity(3);
}




void loop()
{ 
  myTestMatrix.refresh();

}
