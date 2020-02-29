
/* Copyright 2020 Herve Marchand
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "matrixTextScroller.h"


MatrixTextScrollerClass::MatrixTextScrollerClass(int clk, int cs, int din){
  
  Matrix_pinCLK = clk;
  Matrix_pinCS  = cs;
  Matrix_pinDIN = din;

  pinMode(Matrix_pinCLK,OUTPUT);
  pinMode(Matrix_pinCS,OUTPUT);
  pinMode(Matrix_pinDIN,OUTPUT);
  
  initializeMatrix();
  cleanMatrix();
  setIntensity(defaultTextIntensity);
}


void MatrixTextScrollerClass::refresh(){
    
  if(( millis() < lastUpdatePeriodMs || millis() - lastUpdatePeriodMs < Matrix_Text_Update_Period ) ||
     ( 0 == numberOfLoop )) return;
     
  lastUpdatePeriodMs = millis();

  if(0 == displayColumn) {
    lastUpdatePeriodMs = lastUpdatePeriodMs + 20 * Matrix_Text_Update_Period;
  }

  int i;
  for(i = 0; i<8; i++) {
    write_Matrix(i+1, getLineToDisplay(displayColumn, i));
  }

  displayColumn++;
  if(displayColumn > textToDisplayStr.length() * 8 - 1) {
    displayColumn = 0;
    cleanMatrix();
    if(-1 != numberOfLoop) numberOfLoop--;
  }
  
}

void MatrixTextScrollerClass::setTextToDisplay(String textStr){
  textToDisplayStr = " " + textStr;
  numberOfLoop  = -1; // Loop forever
  displayColumn = 0;
  cleanMatrix();
}

void MatrixTextScrollerClass::setTextToDisplayWithLoopNumber(String textStr, int nbLoop){
  textToDisplayStr = " " + textStr;
  numberOfLoop  = nbLoop;
  displayColumn = 0;
  cleanMatrix();
}

// From  0 to 15
void MatrixTextScrollerClass::setIntensity(int intensity){
  // Minimum checking
  if(intensity < 0) intensity = 0;
  if(intensity > 15) intensity = 15;
  
  write_Matrix(0x0A, intensity);  
}


void MatrixTextScrollerClass::cleanMatrix(){
  for(int i=1; i<9; i++) write_Matrix(i, 0x00);
}

void MatrixTextScrollerClass::setTextUpdatePeriod(int period){
  Matrix_Text_Update_Period = period;
}

// --- Private routines ---
void MatrixTextScrollerClass::initializeMatrix(void)
{
  write_Matrix(0x09, 0x00);    // Decode Mode  
  write_Matrix(0x0a, 0x03);    // Intensity
  write_Matrix(0x0b, 0x07);    // Scan Limit 
  write_Matrix(0x0c, 0x01);    // Shutown ON
  write_Matrix(0x0f, 0x00);    // Display Test All Off
}

void MatrixTextScrollerClass::write_Matrix_byte(unsigned char DATA) 
{   
  unsigned char i;
  digitalWrite(Matrix_pinCS,LOW);  
  for(i=8;i>=1;i--)
  {    
    digitalWrite(Matrix_pinCLK,LOW);
    digitalWrite(Matrix_pinDIN,DATA&0x80);
    DATA = DATA<<1;
    digitalWrite(Matrix_pinCLK,HIGH);
  }                                 
}
 
void MatrixTextScrollerClass::write_Matrix(unsigned char address, unsigned char dat)
{
  // dumpPinConfig();
  digitalWrite(Matrix_pinCS,LOW);
  write_Matrix_byte(address);          
  write_Matrix_byte(dat);               
  digitalWrite(Matrix_pinCS,HIGH);
}

int MatrixTextScrollerClass::getMatrixCharEntry(char asciiVal){
  int myEntry = 0;

  if(asciiVal>=93) {
    myEntry = asciiVal - 33;
  } else {
    myEntry = asciiVal - 32;
  }
  if (myEntry < 0 || myEntry > 102) myEntry = 0;

  return myEntry;
}

unsigned char MatrixTextScrollerClass::getLineToDisplay(int column, int line){
  int currentCharInString;
  int entry;

  unsigned char myCharLine;
  unsigned tmpCharLine;

  currentCharInString = floor(column / 8); 

  entry = getMatrixCharEntry(textToDisplayStr.charAt(currentCharInString));

  myCharLine = matrixCharSet[entry][line];
  
  myCharLine = myCharLine << (column - 8 * currentCharInString);


  if(currentCharInString < (textToDisplayStr.length() - 1)) {
    entry = getMatrixCharEntry(textToDisplayStr.charAt(currentCharInString + 1));
    tmpCharLine = matrixCharSet[entry][line];
    tmpCharLine = tmpCharLine >> (8 * (currentCharInString+1) - column);
    myCharLine =  myCharLine | tmpCharLine;
  }

  return myCharLine;
}
