//Zijia Ding
//zxd170230
//zxd170230@utdallas.edu
//CS3377.002

#include "program6.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

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
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  
  //read file
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  ifstream binInFile ("cs3377.bin", ios::in|ios::binary);
  if(!binInFile){
    cout<<"ERROER:Please check .bin file"<<endl;
    return 0;
  }
  binInFile.read((char *) myHeader, sizeof(BinaryFileHeader));
  binInFile.read((char *) myRecord, sizeof(BinaryFileRecord));
  char buffer[32];
  sprintf(buffer, "Magic: %#010X", myHeader->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, buffer);
  sprintf(buffer, "Version: %u", myHeader->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, buffer);
  sprintf(buffer, "NumRecords: %lu",myHeader->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, buffer);

  /* read data record from binary file */
  for (int i = 2; i <= 5; i++)
    {
      sprintf(buffer, "strlen: %i", myRecord->strLength);
      setCDKMatrixCell(myMatrix, i,1, buffer);
      sprintf(buffer, "%s", myRecord->stringBuffer);
      setCDKMatrixCell(myMatrix, i,2, buffer);
    }

  
  drawCDKMatrix(myMatrix, true);    /* required  */

  //pause to see the result
  sleep(10);

  // Cleanup screen
  endCDK();
  binInFile.close();
}
