/*
 * Filename:            main.cc
 * Date:                11/22/2020
 * Author:              Michael Sobieski
 * Email:               mbs180001@utdallas.edu
 * Version:             1.0
 * Copyright:           2020, All Rights Reserved
 *
 * Description:
 *
 *      Build and display a small text based GUI matrix using curses
 *      and the CDK. Then fill the matrix with info from a binary file
 *      obtained from Dr. Perkins.
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <string>
#include <iomanip>
#include <stdint.h>
#include <inttypes.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_ROWS 5
#define MATRIX_COLS 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

const int maxRecordStringLength = 25;

using namespace std;

class BinaryFileHeader
{
public:
  uint32_t magicNumber; // Should be 0xFEEDFACE
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{

  string filename = "/scratch/perkins/cs3377.bin";
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord1 = new BinaryFileRecord();
  BinaryFileRecord *myRecord2 = new BinaryFileRecord();
  BinaryFileRecord *myRecord3 = new BinaryFileRecord();
  BinaryFileRecord *myRecord4 = new BinaryFileRecord();

  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;

  const char *rowTitles[MATRIX_ROWS + 1] = {"IGNORE", "a", "b", "c", "d", "e"};
  const char *columnTitles[MATRIX_COLS + 1] = {"IGNORE", "a", "b", "c"};

  int colWidths[MATRIX_COLS + 1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_COLS + 1] = {vMIXED, vMIXED, vMIXED, vMIXED};


  //Initialize the screen, make sure terminal is fullscreen
  window = initscr();
  cdkscreen = initCDKScreen(window);

  initCDKColor();

  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_ROWS, MATRIX_COLS, MATRIX_ROWS, MATRIX_COLS,
			    MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, colWidths, boxTypes,
			    1, 1, ' ', ROW, true, true, false);
  if(myMatrix == NULL)
    {
      cout << "Error creating matrix" << endl;
      _exit(1);
    }
  drawCDKMatrix(myMatrix, true);






  ifstream binInFile("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  if(!binInFile.good())
    cout << "Error Opening file" << endl;

  stringstream ss;
  string str;
  ss.str("");
  ss.clear();

  if(binInFile.read((char*) myHeader, sizeof(BinaryFileHeader)))
    {
    //Set the header magic number cell
    unsigned long int x(myHeader->magicNumber);
    ss << "Magic: 0x" << uppercase << hex << x << dec << nouppercase;
    str = ss.str();
    setCDKMatrixCell(myMatrix, 1, 1, str.c_str());
    drawCDKMatrix(myMatrix, true);
    ss.str("");
    ss.clear();

    //Set the header version cell
    unsigned long int y(myHeader->versionNumber);
    ss << "Version: " << y ;
    str = ss.str();
    setCDKMatrixCell(myMatrix, 1, 2, str.c_str());
    drawCDKMatrix(myMatrix, true);
    ss.str("");
    ss.clear();

    //Set the header num records cell
    unsigned long int z(myHeader->numRecords);
    ss << "NumRecords:  " << z ;
    str = ss.str();
    setCDKMatrixCell(myMatrix, 1, 3, str.c_str());
    drawCDKMatrix(myMatrix, true);
    ss.str("");
    ss.clear();


    }

  if(binInFile.read((char*) myRecord1, sizeof(BinaryFileRecord)))
  {

    //Set the record strlen column
    unsigned long int a(myRecord1->strLength);
    ss << "strlen:  " << a ;
    str = ss.str();
    setCDKMatrixCell(myMatrix, 2, 1, str.c_str());
    drawCDKMatrix(myMatrix, true);
    ss.str("");
    ss.clear();

     //Set the record name column
    setCDKMatrixCell(myMatrix, 2, 2, (myRecord1->stringBuffer));
    drawCDKMatrix(myMatrix, true);
  }
  if(binInFile.read((char*) myRecord2, sizeof(BinaryFileRecord)))
  {
     //Set the record strlen column
    unsigned long int b(myRecord2->strLength);
    ss << "strlen:  " << b ;
    str = ss.str();
    setCDKMatrixCell(myMatrix, 3, 1, str.c_str());
    drawCDKMatrix(myMatrix, true);
    ss.str("");
    ss.clear();

     //Set the record name column
    setCDKMatrixCell(myMatrix, 3, 2, (myRecord2->stringBuffer));
    drawCDKMatrix(myMatrix, true);
  }
  if(binInFile.read((char*) myRecord3, sizeof(BinaryFileRecord)))
  {
     //Set the record strlen column
    unsigned long int c(myRecord3->strLength);
    ss << "strlen:  " << c;
    str = ss.str();
    setCDKMatrixCell(myMatrix, 4, 1, str.c_str());
    drawCDKMatrix(myMatrix, true);
    ss.str("");
    ss.clear();

     //Set the record name column
    setCDKMatrixCell(myMatrix, 4, 2, (myRecord3->stringBuffer));
    drawCDKMatrix(myMatrix, true);
  }
  if(binInFile.read((char*) myRecord4, sizeof(BinaryFileRecord)))
  {
     //Set the record strlen column
    unsigned long int d(myRecord4->strLength);
    ss << "strlen:  " << d ;
    str = ss.str();
    setCDKMatrixCell(myMatrix, 5, 1, str.c_str());
    drawCDKMatrix(myMatrix, true);
    ss.str("");
    ss.clear();

     //Set the record name column
    setCDKMatrixCell(myMatrix, 5, 2, (myRecord4->stringBuffer));
    drawCDKMatrix(myMatrix, true);
  }


 binInFile.close();

 sleep(10);
 endCDK();

 return 0;
}


