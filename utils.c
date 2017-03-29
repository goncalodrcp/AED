/******************************************************************************
 *lol
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
#include "Puzzle.h"
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
 * Arguments:  fm - pointer to the file with the Puzzles
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: save the Puzzles in fm, into mA.
 *****************************************************************************/
t_lista *savePuzzles( FILE *fm )
{

  t_lista *lm;
  t_puzzle *newPuzzle;

  int m_size = 0;
  int pJ, pI, err;
  int NumberPuzzles = 0;
  float newEntry = 0.0;

  printf("--> Loading Puzzles...");

  lm = iniLista();


  while( 1 ){

    /* scan the size of the Puzzle NumberPuzzles */
    if( fscanf( fm, "%d", &m_size ) != 1 )
      break;

    /* verify if size is correct */
    if( m_size < 2 || m_size > 9 )
      erroFileData();

    /* create a new Puzzle */
    newPuzzle = NewPuzzle( m_size );

    /* save the Puzzle */
    for( pI = 0 ; pI < m_size ; pI++ ){
      for( pJ = 0 ; pJ < m_size ; pJ++ ){
        if( fscanf( fm, "%f", &newEntry ) != 1 )
          erroFileData();
        SetPuzzleElement(newPuzzle, pI, pJ, newEntry);
      }
    }

    NumberPuzzles++;
    lm = criaNovoNoLista (lm, newPuzzle, &err);
  }

  printf( "[DONE]\n" );
  return lm;

}


/******************************************************************************
 *  PrintList ()
 *
 * Arguments:  lm - pointer to the list
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: print the list of Puzzles.
 *****************************************************************************/
void PrintList(t_lista *lm){

  t_lista *aux;
  t_puzzle *mA;

  printf("--> Printing items saved in memory...\n");

  aux = lm;
  while( aux!= NULL ){
    mA = (t_puzzle *)getItemLista( aux );
    PrintPuzzle( mA );
    aux = getProxElementoLista( aux );
  }

  printf( "...[DONE]\n" );

  return;

}

FILE *open_file( char *nome, char *mode )
{
  FILE *f;
  f = fopen ( nome, mode );
  if ( f == NULL ) {
    fprintf ( stderr, "ERROR: It is not possible to open file %s!\n", nome );
    exit ( 1 );
    /* Error messages are sent to the stderr channel.
       Use an exit number different from 0 (zero) in case of error.*/
  }
  return (f);
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
