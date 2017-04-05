/******************************************************************************
 *
 * File Name: main.c
 *	      (c) 2010 AED
 * Authors:    AED Team
 * Last modified: ACR 2017-03-19
 *
 * COMMENTS
 *		Main program
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzzle.h"
#include "list.h"
#include "utils.h"

/******************************************************************************
 * Usage ()
 *
 * Arguments: nomeProg - name of executable
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: message function when arguments are missing
 *
 *****************************************************************************/
void Usage(char *nomeProg)
{

  printf("Usage: %s [filename]\n",
      nomeProg);

  exit(1);

}

/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int
 * Side-Effects: none
 *
 * Description: main Program
 *
 *****************************************************************************/
int main(int argc, char *argv[])
{

  char *fileName;
  FILE *fmIn;
  t_lista *lp;

  /* check if the program was correctly executes */
  if( argc < 2 )
    Usage( argv[0] );

  /* open the file with the Puzzles */
  fileName = argv[1];
  fmIn = fopen( fileName, "r" );
  if( fmIn == NULL ){
    printf( "Open error of the input file\n" );
    exit(2);
  }

  /* read and save the Puzzles in the list */
  lp = savePuzzles( fmIn );


  OrganizeList(lp);

  /* print list (optional) */
  outputFile(fileName, lp);

  /* free all alocated memory */
  libertaLista( lp, FreeItem );

  /* close the file */
  fclose(fmIn);

  exit(0);
}
