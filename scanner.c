/*
 ============================================================================
 Name        : scanner.c
 Author      : NGUYEN, TAM N
 Created on  : 15OCT16
 Version     : 1
 Copyright   : (CC)
 Summary	 : Implementation of scanner ADT's functions. ADT definition and
                implementation is in scanner.h
 Functions	 : myScanner initScanner ()
                printDriverTable (myScanner source)
                myScanner scanByStream(FILE *fp)
                myScanner scanByName(const char *filename)
                void clearScanner(myScanner s)
                
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./scanner.h"

//define implicit file ext here
static const char fileExt[10] = ".fs16";


/*****************
 * Function:
 *      initScanner
 * Description: 
 *      Allocate memory needed for the scanner ADt
 *      Populate the driver table with default values
 *      Please refer to README.md for details regarding
 *      automaton and mapped driver table.
 * Input:
 *      none
 * Output:
 *      a scanner ADT with memory allocated and default values populated
 *****************/
myScanner initScanner () {
    
    myScanner    s;
    // allocate memory for scanner
	s = malloc(sizeof(struct Scanner));
    
    //HARD CODE DRIVER TABLE HERE
    
    //step 1 - filling table with ERROR code "980"
    int i,j;
    for (i = 0; i<16; i++){                             // 16 rows - 16 states
        for (j = 0; j<24; j++) {                        // 24 columns - 24 sets of values
            s->table[i][j] = invalidToken_errorCode;
        }
    }
    //step 2 - filling in TOKEN codes (defined in token.h file)
    for (i=2; i<24; i++) s->table[1][i] = idCode;       //991 : Identifier Token
    for (i = 0; i<16; i++){         
        for (j = 0; j<24; j++) {        
            //Fill the "Relational" token code
            if (i==2 || i==4 || i==5 || i==7 || i==8 || i==10 ){
                if (j==0 || j==1 || j==2 || (j>=8 && j<=13) ||j==15 ||j==18 ||j==21 ){
                    s->table[i][j] = relCode;           //992 : Relational Token
                }
            }
            //Fill the "Other" token code
            if (i==11){
                if (j==0 || j==1 || j==2 ||(j>=8 && j<=13) ||j==15 ||j==18 ||j==21 ){
                    s->table[i][j] = otherCode;       //993 : Other Token
                }
            }
            if (i==12){
                if (j==0 || j==1 || j==2 || j==15 ||j==18 ||j==21 ){
                    s->table[i][j] = otherCode;       //993 : Other Token
                }
            }
            //Fill the "Delimiter" token code
            if (i==13){
                if (j==0 || j==1 || j==2 || (j>=8 && j<=13)) {
                    s->table[i][j] = delimCode;       //994 : Delimiter Token
                }
            }
            //Fill the "Integer" token code
            if (i==14){
                if ((j>=2 && j<=5) || (j>=8 && j<=13) || (j>=15 && j<=22)) {
                    s->table[i][j] = intCode;       //995 : Integer Token
                }
            }
            //Fill in the "Comment" token code
            s->table[15][2] = comCode;      //995 : Comment token
        }
        s->table[i][24] = invalidCharacter_errorCode;  // fill col 24 with invalidCharacter_errorCode 
    }
    
    //step 3 - filling in STATE codes (in asscending state code order)
    s->table[0][2] = 0;
    s->table[0][0] = s->table[1][0] = s->table[1][1] = 1;
    s->table[0][3] = 2;
    s->table[2][6] = 3;
    s->table[3][3] = 4;
    s->table[0][4] = 5;
    s->table[5][3] = 6;
    s->table[6][4] = 7;
    s->table[0][5] = 8;
    s->table[8][3] = 9;
    s->table[9][5] = 10;
    s->table[2][3] = 11;
    for (i = 7; i<14; i++) s->table[0][i] = 12;
    for (i = 14; i<23; i++) s->table[0][i] = 13;
    s->table[0][1] = s->table[14][1] = 14;
    s->table[0][23] = s->table[15][0] = s->table[15][1] = 15;
    for (i = 3; i<24; i++) s->table[15][i] = 15;
    
    return s;
    
}

/*****************
 * Function:
 *      printDriverTable
 * Description:
 *      This function is for troubleshooting purpose. 
 *      It prints the currenet hardcoded driver table out to the screen.
 *      By defailt, this function is not available publicly.
 * Input:
 *      A scanner ADT
 * Output:
 *      Printing out corresponding scanner ADT's driver table
 *****************/
void printDriverTable (myScanner source) {
    int i,j;
    for (i = 0; i<16; i++){             // 16 rows - 16 states
    printf("\n");
        for (j = 0; j<24; j++) {        // 24 columns - 24 sets of values
            if (source->table[i][j] == invalidToken_errorCode){
                printf("    .");        // for presentation purpose
            }
            else 
                printf("%5i",source->table[i][j]);
        }
    } 
    printf("\n");
    
}


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
myScanner scanByStream(FILE *fp)
{
    myScanner a;
    a = initScanner();
	if (fp == NULL) {
	    fprintf (stderr,"ERROR: Content stream is empty \n");
	    return NULL;
    }
	a->fp = fp;	

	return a;
}

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
myScanner scanByName(const char *filename)
{
	strcat (filename, fileExt);
	FILE* filePtr = fopen (filename, "r");
	//if that is a bogus argument or file is not readable
	if (filePtr == NULL){
			fprintf (stderr,"ERROR: file '%s' does not exist or not readable \n", filename);
			return NULL;
	}
	return scanByStream(filePtr);
}

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
void clearScanner(myScanner s)
{
	// de-allocate memory
	if (s != NULL) {
		free(s);
	}
}