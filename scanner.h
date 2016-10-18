/*
 ============================================================================
 Name        : scanner.h
 Author      : NGUYEN, TAM N
 Created on  : 15OCT16
 Version     : 1
 Copyright   : (CC)
 Summary	 : A basic scanner using pointer to read content from a file name
                or from a stream of information. The ADT implementation is made
                available globally so other ADT can reference to it.
                An important feature of this ADT is the data table which dictate
                how scanned data can be interpreted.
 
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

/*****************
 * Function:
 *      scanByName
 * Description: 
 *      Create a scanner pointer from file name.
 *      The file name extention is implicit (default is ".fs16")
 * Input:
 *      a string of the file's name (read from CLI)
 * Output:
 *      returning a scanner ADT
 *****************/
myScanner scanByName(const char *filename);


/*****************
 * Function:
 *      scanByStream
 * Description: 
 *      Create a scanner pointer pointed to stdin (a file redirection stream or a keyboard stream).
 * Input:
 *      stdin
 * Output:
 *      returning a scanner ADT
 *****************/
myScanner scanByStream(FILE *fp);


/*****************
 * Function:
 *      clearScanner
 * Description: 
 *      free up memory used by a scanner ADT
 * Input:   
 *      a scanner ADT
 * Output:
 *      released memory previously occupied by the scanner ADT
 *****************/
void clearScanner(myScanner);


#endif