/******************************************************************************
 *
 * File Name: Puzzle.h
 *	      (c) 2017 AED
 * Authors:    AED Team
 * Last modified: ACR 2017-03-19
 *
 * COMMENTS
 *		Structure and prototypes for type t_puzzle
 *		t_puzzle includes a Puzzle and a function Puzzle value
 *
 *****************************************************************************/

#ifndef _PUZZLE_H
#define _PUZZLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* type definition for structure to hold word */
typedef struct _t_puzzle t_puzzle;

/* interface functions for the t_puzzle */
t_puzzle *NewPuzzle(int size);
float GetPuzzleElement(t_puzzle *mA, int pI, int pJ);
void SetPuzzleElement(t_puzzle *mA, int pI, int pJ, float value);
void FreePuzzle(t_puzzle *mA);
void PrintPuzzle(t_puzzle *mA);

#endif
