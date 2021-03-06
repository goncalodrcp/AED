/******************************************************************************
 *
 * File Name: utils.c
 *	      (c) 2017 AED
 * Authors:    AED Team
 * Last modified: ACR 2017-03-19
 *
 * COMMENTS
 *		Useful functions
 *
 *****************************************************************************/

#include "defs.h"
#include "puzzle.h"
#include "list.h"
#include "utils.h"

/******************************************************************************
 * erroMemoria ()
 *
 * Arguments: msg - pointer to message to print
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: print to standard error output an allocation error message
 *****************************************************************************/
void erroMemoria( char *msg )
{

  fprintf(stderr, "Error during memory reserve attempt.\n");
  fprintf(stderr, "Msg: %s\n",msg);
  fprintf(stderr, "Exit Program due to unmanaged error.\n");

  exit(1);
}

/******************************************************************************
 * erroFileData ()
 *
 * Arguments: msg - pointer to message to print
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: print to standard error output an allocation error message
 *****************************************************************************/
void erroFileData( )
{

  fprintf(stderr, "ERROR: file data is currupted.\n");

  exit(1);
}


/******************************************************************************
 *  savePuzzles ()
 *
 * Arguments:  fp - pointer to the file with the Puzzles
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: save the Puzzles in fp, into lp.
 *****************************************************************************/
t_lista *savePuzzles( FILE *fp )
{

  t_lista *lp;
  t_puzzle *newPuzzle;

  int pJ, pI, err;
  int NumberPuzzles = 0;
  int newEntry = 0;
  int puz_dt[5];

  printf("--> Loading Puzzles...");

  lp = iniLista();


  while( 1 ){

    /* scan the information about the Puzzle */
    if( fscanf( fp, "%d %d %d %d %d", &puz_dt[0], &puz_dt[1], &puz_dt[2], &puz_dt[3], &puz_dt[4]) != 5 )
      break;

    /* create a new Puzzle */
    newPuzzle = NewPuzzle( puz_dt );

    /* save the Puzzle */
    for( pI = 0 ; pI < puz_dt[0] ; pI++ ){
      for( pJ = 0 ; pJ < puz_dt[1] ; pJ++ ){
        if( fscanf( fp, "%d", &newEntry ) != 1 )
        {
          erroFileData();
        }

        newPuzzle->values[pI][pJ] = newEntry;
        
      }
    }

    NumberPuzzles++;
    lp = criaNovoNoLista (lp, newPuzzle, &err);
  }

  printf( "[DONE]\n" );
  return lp;

}


/******************************************************************************
 *  PrintList ()
 *
 * Arguments:  lp - pointer to the list
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: print the list of Puzzles.
 *****************************************************************************/
void PrintList(t_lista *lp, FILE * fp){

  t_lista *aux;
  t_puzzle *pz;

  printf("--> Printing items saved in memory...");

  aux = lp;
  while( aux!= NULL ){
    pz = (t_puzzle *)getItemLista( aux );
    PrintPuzzle( pz, fp );
    aux = getProxElementoLista( aux );
  }

  printf( "...[DONE]\n" );

  return;
}

void OrganizeList(t_lista *lp){

  t_lista *aux;
  t_puzzle *pz;

  printf("--> Organizing Puzzles ...");

  aux = lp;
  while( aux!= NULL ){
    pz = (t_puzzle *)getItemLista( aux );
    OrganizePuzzle(pz);
    aux = getProxElementoLista( aux );
  }

  printf( "...[DONE]\n" );

  return;
}

/******************************************************************************
 *  outputFile ()
 *
 * Arguments:  inName - string of the data file
 *             lp - pointer to list
 * Returns: (void)
 * Side-Effects: outputs a file with the resultes of the program
 *
 * Description: prints the list to a new file called "inName.step" .
 *****************************************************************************/
void outputFile(char *inName, t_lista* lp){

  FILE *fp;
  char *outName;
  int len = strlen(inName);

  /* Allocates space for out file name, ading the  "\0" and the char missing in "txt" used in "step"*/
  outName = (char*)malloc((len+1+1)*sizeof(char));
  if ( outName == NULL ) {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 5 );
  }
  inName[len-3] = '\0';

  strcpy ( outName, inName );
  strcat ( outName, "step" );

  fp = fopen(outName, "w");
  PrintList(lp, fp);

  fclose ( fp );
  free(outName);
  return;

}

/******************************************************************************
 * FreeItem ()
 *
 * Arguments: p - pointer to Item
 * Returns: (void)
 * Side-Effects: calls function to free word structure
 *
 * Description: interfaces generic list item to specific Puzzle structure
 *
 *****************************************************************************/
void FreeItem( Item this )
{

  FreePuzzle( (t_puzzle *)this );

  return;
}
