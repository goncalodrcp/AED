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
  int **values;
  int l, c, x, y, var, pts;
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
t_puzzle * NewPuzzle(int *puz_dt )
{
  t_puzzle * mA;
  int pI, pJ;
  pI = pJ = 0;

  /* allocate space for the Puzzle */
  mA = (t_puzzle*) malloc(sizeof(t_puzzle));
  mA->values = (int**) malloc(puz_dt[0] * sizeof(int*));
  for ( pI = 0; pI < puz_dt[0]; pI++ )
    mA->values[pI] = (int *) malloc(puz_dt[1] * sizeof(int));
 
  /* initiate Puzzle */
  for ( pI =0; pI < puz_dt[0]; pI++ )
    for ( pJ =0; pJ < puz_dt[1]; pJ++ )
      mA->values[pI][pJ] = 0;
  
  mA->l = puz_dt[0];
  mA->c = puz_dt[1];
  mA->var = puz_dt[2];
  mA->x = puz_dt[3];
  mA->y = puz_dt[4];
  mA->pts = 0;

  return mA;

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
int GetPuzzleElement(t_puzzle *mA, int pI, int pJ)
{

  return mA->values[pI][pJ];

}

/******************************************************************************
 * GetPuzzleInfo(t_puzzle *mA, int info)
 *
 * Arguments: mA - (Puzzle *) the Puzzle
 *            info - (int) what information about the puzzle is neded (1-Lines;
                      2-Columns; 3-Variable; 4-Line chosen; 5-Column chosen;
                      6-Points)
 *          
 * Returns: (float) the value of the Puzzle that is in (pI, pJ)
 * Side-Effects: none
 *
 * Description: returns an element in the Puzzle (mA) in position (pI,pJ)
 *****************************************************************************/

int GetPuzzleInfo(t_puzzle *mA, int info)
{
  switch(info) {
    case '1' :
      return mA->l;
    case '2' :
      return mA->c;
    case '3' :
      return mA->x;
    case '4' :
      return mA->y;
    case '5' :
      return mA->var;
    case '6' :
      return mA->pts;
    default :
      return -1;
   }

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
  
  for(i=0; i<mA->l; i++)
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
void PrintPuzzle(t_puzzle *mA, FILE* fp)
{
 
  int pI, pJ;

  fprintf(fp, "%d %d %d %d %d \n", mA->l, mA->c, mA->var, mA->x, mA->y);
  if(mA->var==1)
    fprintf(fp, "%d\n", mA->pts);
  if(mA->var==2)
  {
    for( pI = 0; pI < mA->l ; pI++ ){
      for( pJ = 0; pJ < mA->c ; pJ++ )
        fprintf(fp ,"%d", GetPuzzleElement( mA, pI, pJ ) );
      fprintf(fp, "\n" );
    
      }
  }
  return;

}
