/******************************************************************************
 *
 * File Name: utils.h
 *	      (c) 2019 AED
 * Authors:    AED Team
 * Last modified: ACR 2017-03-19
 *
 * COMMENTS
 *		Useful functions
 *
 *****************************************************************************/

#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "defs.h"
#include "list.h"
#include "puzzle.h"


void erroMemoria(char *msg);
t_lista *savePuzzles( FILE *fm);
void PrintList(t_lista *lm, FILE *fm);
void outputFile(char *inName, t_lista* lp);
void FreeItem(Item this);


#endif
