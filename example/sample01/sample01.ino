#include "matrixTextScroller.h"
 
int pinCLK = 10;
int pinCS  = 11;
int pinDIN = 12;

MatrixTextScrollerClass myTestMatrix = MatrixTextScrollerClass(pinCLK, pinCS, pinDIN);

void setup()
{

  Serial.begin(115200); // open the serial port at 9600 bps:

  myTestMatrix.setTextToDisplay("This is my text", -1);
  myTestMatrix.setTextUpdatePeriod(35);
  myTestMatrix.setIntensity(3);
}




void loop()
{ 
  myTestMatrix.refresh();

}
