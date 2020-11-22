/*
 * Filename:            cdkexample.cc
 * Date:                11/08/2020
 * Author:              Stephen Perkins
 * Email:               stephen.perkins@utdallas.edu
 * Version:             1.0
 * Copyright:           2020, All Rights Reserved
 *
 * Description:
 *
 *      Build and display a small text based GUI matrix using curses
 *      and the CDK.
 */

#include <iostream>
#include "cdk.h"

/*
 * For grins and giggles, we will define values using the C
 * Preprocessor instead of C or C++ data types.  These symbols (and
 * their values) get inserted into the Preprocessor's symbol table.
 * The names are replaced by their values when seen later in the code.
 */

#define MATRIX_ROWS 6
#define MATRIX_COLS 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // CDK uses offset 1 and C/C++ use offset 0.  Therefore, we create one more 
  // slot than necessary and ignore the value at location 0.
  const char 		*rowTitles[MATRIX_ROWS+1] = {"IGNORE", "R1", "R2", "R3", "R4", "R5", "R6"};
  const char 		*columnTitles[MATRIX_COLS+1] = {"IGNORE", "C1", "C2", "C3"};
  int		colWidths[MATRIX_COLS+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_COLS+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_ROWS, MATRIX_COLS, MATRIX_ROWS, MATRIX_COLS,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, colWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}
