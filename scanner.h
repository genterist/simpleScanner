/*
 ============================================================================
 Name        : scanner.h
 Author      : NGUYEN, TAM N
 Created on  : 15OCT16
 Version     : 1
 Copyright   : (CC)
 Summary	 : 
 ============================================================================
 */

#ifndef _SCANNER_H_
#define _SCANNER_H_


typedef struct Scanner *myScanner; 
struct Scanner {
	FILE   *fp;				        // input stream
    int     table[100][100];        // table max value is 100 for each dimension
};

#include <stdio.h>
#include "./token.h"

myScanner scanByName(const char *filename);
myScanner scanByStream(FILE *fp);

void printDriverTable (myScanner);
/*Free up memory used by the scanner
*/
void clearScanner(myScanner);


#endif