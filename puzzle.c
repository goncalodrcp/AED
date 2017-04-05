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
#include "defs.h"
#include <strings.h>
#include "puzzle.h"
#include "utils.h"

/*struct _t_puzzle {
  int **values;
  int l, c, x, y, var, pts;
};*/

/******************************************************************************
 * *NewPuzzle(int *puz_dt)
 *
 * Arguments: puz_dt - Configuration parameters
 * Returns: (Puzzle *) pointer to actual word (string)
 * Side-Effects: none
 *
 * Description: returns the new Puzzle
 *****************************************************************************/
t_puzzle * NewPuzzle(int *puz_dt )
{
  t_puzzle * pz;
  int pI, pJ;
  pI = pJ = 0;

  /* allocate space for the Puzzle */
  pz = (t_puzzle*) malloc(sizeof(t_puzzle));
  pz->values = (int**) malloc(puz_dt[0] * sizeof(int*));
  for ( pI = 0; pI < puz_dt[0]; pI++ )
    pz->values[pI] = (int *) malloc(puz_dt[1] * sizeof(int));

  /* initiate Puzzle */
  for ( pI =0; pI < puz_dt[0]; pI++ )
    for ( pJ =0; pJ < puz_dt[1]; pJ++ )
      pz->values[pI][pJ] = 0;

  pz->l = puz_dt[0];
  pz->c = puz_dt[1];
  pz->var = puz_dt[2];
  pz->x = puz_dt[3];
  pz->y = puz_dt[4];
  pz->pts = 0;

  return pz;

}

/******************************************************************************
 * GetPuzzleInfo(t_puzzle *pz, int info)
 *
 * Arguments: pz - (Puzzle *) the Puzzle
 *            info - (int) what information about the puzzle is neded (1-Lines;
                      2-Columns; 3-Variable; 4-Line chosen; 5-Column chosen;
                      6-Points)
 *
 * Returns: (int) the value of the Puzzle that is in (pI, pJ)
 * Side-Effects: none
 *
 * Description: returns an element in the Puzzle (pz) in position (pI,pJ)
 *****************************************************************************/

int GetPuzzleInfo(t_puzzle *pz, int info)
{
  switch(info) {
    case '1' :
      return pz->l;
    case '2' :
      return pz->c;
    case '3' :
      return pz->x;
    case '4' :
      return pz->y;
    case '5' :
      return pz->var;
    case '6' :
      return pz->pts;
    default :
      return -1;
   }

}

/******************************************************************************
 * FreePuzzle(t_puzzle *pz)
 *
 * Arguments: pz - (t_puzzle *) the Puzzle
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: free all the memory associated with the Puzzle pz
 *****************************************************************************/
void FreePuzzle(t_puzzle *pz)
{
  int i=0;

  for(i=0; i<pz->l; i++)
    free(pz->values[i]);
  free(pz->values);
  free(pz);

  return;
}

/******************************************************************************
 * PrintPuzzle(t_puzzle *pz)
 *
 * Arguments: pz - (t_puzzle *) the Puzzle
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: print the Puzzle pointed by pz
 *****************************************************************************/
void PrintPuzzle(t_puzzle *pz, FILE* fp)
{

  int pI, pJ;

  fprintf(fp, "%d %d %d %d %d \n", pz->l, pz->c, pz->var, pz->x, pz->y);
  if(pz->var==1)
    fprintf(fp, "%d\n", pz->pts);
  if(pz->var==2)
  {
    for( pI = 0; pI < pz->l ; pI++ ){
      for( pJ = 0; pJ < pz->c ; pJ++ )
        fprintf(fp ,"%d ", pz->values[pI][pJ] );
      fprintf(fp, "\n" );

    }
    fprintf(fp,"\n");
  }
  return;

}

void OrganizePuzzle(t_puzzle *pz)
{
	int pJ;

	for(pJ = 0; pJ < pz->c; pJ++)
		pushDown(pz->values, pz->l, pJ);

  pushRight(pz->values, pz->l, pz->c);

}

void pushDown(int **mA, int l, int c_select)
{
	int pI_a, pI_b;

  /* pointer a detectes a espace to fill with a number */
	pI_a = l-1;
	while(pI_a > 0) {
    /* pointer a detectes a espace to fill with a number */
		if(mA[pI_a][c_select] == -1) {
			pI_b = pI_a - 1;
			while(pI_b >= 0) {
        /* pointer b detects a number to fill the space in pointer */
				if(mA[pI_b][c_select] != -1) {
					mA[pI_a][c_select] = mA[pI_b][c_select];
					mA[pI_b][c_select] = -1;
          /*the espace if filld, pointer a moves to the next one*/
          pI_a--;
				}

				pI_b--;
				/*in case it reaches the end of the column and finds no numbers exits the function */
				if(pI_b<0)
					return;
			}

		}
    pI_a--;
	}
	return;
}


void pushRight(int **mA, int l, int c)
{
  int pJ_a, pJ_b, pI;

  /* pointer a detectes a espace to fill with a number */
  pJ_a = c-1;
  while(pJ_a > 0) {
    /* pointer a detectes a espace to fill with a number */
    if(mA[l-1][pJ_a] == -1 ) {
      pJ_b = pJ_a - 1;
      while(pJ_b >= 0) {
        /* pointer b detects a number to fill the space in pointer */
        if(mA[l-1][pJ_b] != -1) {
          pI = l - 1;
          printf("\n!!!1!!!\n");
          while((pI >= 0) && (mA[pI][pJ_b] != -1)){
            printf("\n!!!2!!!\n");
            mA[pI][pJ_a] = mA[pI][pJ_b];
            mA[pI][pJ_b] = -1;
            pI--;
          }
          /*the espace if filld, pointer a moves to the next one*/
          pJ_a--;
        }

        pJ_b--;
        /*in case it reaches the end of the column and finds no numbers exits the function */
        if(pJ_b<0)
          return;
      }
    }
    pJ_a--;
  }
  return;
}