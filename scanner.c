/*
 ============================================================================
 Name        : traversals.c
 Author      : NGUYEN, TAM N
 Created on  : 15OCT16
 Version     : 1
 Copyright   : (CC)
 Summary	 : 
 Functions	 :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

struct Scanner {
	FILE   *fp;				// input stream
    int     table[][];
};

void initTable {
    
}

myScanner scanByStream(FILE *fp)
{	
	Scanner    s;
	
	if (fp == NULL) {
	    fprintf (stderr,"ERROR: Content stream is empty \n");
	    return NULL;
    }

	
	// allocate memory for scanner
	s = malloc(sizeof(struct Scanner));

	// initialize
	s->fp = fp;	

	return s;
}

Scanner scanByName(const char *filename)
{
	FILE* filePtr = fopen (filename, "r");
	//if that is a bogus argument or file is not readable
	if (filePtr == NULL){
			fprintf (stderr,"ERROR: file '%s' does not exist or not readable \n", filename);
			return NULL;
	}
	return scanByStream(filePtr);
}


void clearScanner(Scanner s)
{
	// de-allocate memory
	if (s != NULL) {
		free(s);
	}
}


