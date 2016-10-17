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

typedef enum {false, true} bool;
typedef struct Scanner *myScanner; 
typedef struct Token *myToken;

#include <stdio.h>

myScanner scanByName(const char *filename);
myScanner scanByStream(FILE *fp);

void printDriverTable (myScanner);

/*Free up memory used by the scanner
*/
void clearScanner(myScanner);


#endif