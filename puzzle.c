/******************************************************************************
 *
 * File Name: puzzle.c
 *	      (c) 2017 AED
 * Authors:    AED Team
 * Last modified: ACR 2017-03-19
 *
 * COMMENTS
 *		implements functions for type t_puzzle
 *
 *****************************************************************************/

#include <strings.h>
#include "puzzle.h"
#include "utils.h"

struct _t_puzzle {
  float **values;
  int l, c, x, y, var;
};

/******************************************************************************
 * *NewPuzzle(int size)
 *
 * Arguments: size - size of the square Puzzle (size x size)
 * Returns: (Puzzle *) pointer to actual word (string)
 * Side-Effects: none
 *
 * Description: returns the new Puzzle
 *****************************************************************************/
t_puzzle *NewPuzzle(int size)
{

  int pI, pJ;
  pI = pJ = 0;

  /* allocate space for the Puzzle */
  t_puzzle *Mat = (t_puzzle*) malloc(sizeof(t_puzzle));
  Mat->values = (float**) malloc(size*sizeof(float*));
  for ( pI = 0; pI < size; pI++ )
    Mat->values[pI] = (float *) malloc(size*sizeof(float));

  /* initiate Puzzle */
  for ( pI =0; pI < size; pI++ )
    for ( pJ =0; pJ < size; pJ++ )
      Mat->values[pI][pJ] = 0.0;

  Mat->fm = 0;
  Mat->size = size;

  return Mat;

}

/******************************************************************************
 * GetPuzzleElement(Puzzle *mA, int pI, int pJ)
 *
 * Arguments: mA - (Puzzle *) the Puzzle
 *            pI - (int) row of the element
 *            pJ - (int) column if the element
 * Returns: (float) the value of the Puzzle that is in (pI, pJ)
 * Side-Effects: none
 *
 * Description: returns an element in the Puzzle (mA) in position (pI,pJ)
 *****************************************************************************/
float GetPuzzleElement(t_puzzle *mA, int pI, int pJ)
{

  return mA->values[pI][pJ];

}

/******************************************************************************
 * SetPuzzleElement(t_puzzle *mA, int pI, int pJ, float value)
 *
 * Arguments: mA    - (t_puzzle *) the Puzzle
 *            pI    - (int) row of the element
 *            pJ    - (int) column if the element
 *            value - (float) value to include int the Puzzle
 * Returns: (void) nothing
 * Side-Effects: none
 *
 * Description: function to include an element (value) in the Puzzle (mA),
 *              in position (pI, pJ)
 *****************************************************************************/
void SetPuzzleElement(t_puzzle *mA, int pI, int pJ, float value)
{

  mA->values[pI][pJ] = value;

  return;

}




/******************************************************************************
 * FreePuzzle(t_puzzle *mA)
 *
 * Arguments: mA - (t_puzzle *) the Puzzle
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: free all the memory associated with the Puzzle mA
 *****************************************************************************/
void FreePuzzle(t_puzzle *mA)
{
  int i=0;

  for(i=0; i<mA->size; i++)
    free(mA->values[i]);
  free(mA->values);
  free(mA);

  return;
}

/******************************************************************************
 * PrintPuzzle(t_puzzle *mA)
 *
 * Arguments: mA - (t_puzzle *) the Puzzle
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: print the Puzzle pointed by mA
 *****************************************************************************/
void PrintPuzzle(t_puzzle *mA)
{

  int pI, pJ;

  printf( "Puzzle:\n" );
  for( pI = 0; pI < mA->size ; pI++ ){
    for( pJ = 0; pJ < mA->size ; pJ++ )
      printf( "%.2f ", GetPuzzleElement( mA, pI, pJ ) );
    printf( "\n" );
  }

  printf( "With Puzzle function value: %.2f\n", GetFunctionPuzzleValue( mA ) );

  return;

}

void write_file(char *filename, t_lista* lp)
{
  FILE *f;
  char *nome;
  int i = 0;
  int j = 0;
  int count = 0;

  nome = (char*)malloc((strlen(filename)+1)*sizeof(char)); /* -- Insert code for memory allocation,  remember to add space for the dot (.), the filename extension and the string termination --*/
  if ( nome == NULL ) {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 5 );
  }

  while(filename[j] != '\0')
  {
    count++;
    j++;
  }

  for(j = count; j <= count-2; j--)
  {
    free(filename[j]);
  }

  filename[count-2] = '\0';

  strcpy ( nome, filename );
  strcat ( nome, "step" );

  PrintList(lp);

  fclose ( f );
  free(nome);
  return;

}
