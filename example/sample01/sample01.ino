#include "matrixTextScroller.h"
 
int pinCLK = 10;
int pinCS  = 11;
int pinDIN = 12;

MatrixTextScrollerClass myTestMatrix = MatrixTextScrollerClass(pinCLK, pinCS, pinDIN);

void setup()
{
  myTestMatrix.setTextToDisplay("This is my text", -1);
  myTestMatrix.setTextUpdatePeriod(35);
  myTestMatrix.setIntensity(3);
}




void loop()
{ 
  myTestMatrix.refresh();

}
