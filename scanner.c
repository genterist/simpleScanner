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

#include "./scanner.h"

//token codes
int errorCode = 980;
int idCode = 991;
int relCode = 992;
int otherCode = 993;
int delimCode = 994;
int intCode = 995;
int comCode = 996;

struct Scanner {
	FILE   *fp;				// input stream
    int     table[100][100];      // table max value is 100 for each dimension
};

myScanner initScanner () {
    
    myScanner    s;
    // allocate memory for scanner
	s = malloc(sizeof(struct Scanner));
    
    //HARD CODE DRIVER TABLE HERE
    
    //step 1 - filling table with general ERROR code "980"
    int i,j;
    for (i = 0; i<16; i++){         // 16 rows - 16 states
        for (j = 0; j<24; j++) {        // 24 columns - 24 sets of values
            s->table[i][j] = errorCode;
        }
    }
    //step 2 - filling in TOKEN codes
    for (i=2; i<24; i++) s->table[1][i] = idCode;      //991 : Identifier Token
    for (i = 0; i<16; i++){         
        for (j = 0; j<24; j++) {        
            //Fill the "Relational" token code
            if (i==2 || i==4 || i==5 || i==7 || i==8 || i==10 ){
                if (j==0 || j==1 || j==2 || (j>=8 && j<=13) ||j==15 ||j==18 ||j==21 ){
                    s->table[i][j] = relCode;       //992 : Relational Token
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

void printDriverTable (myScanner source) {
    int i,j;
    for (i = 0; i<16; i++){         // 16 rows - 16 states
    printf("\n");
        for (j = 0; j<24; j++) {        // 24 columns - 24 sets of values
            if (source->table[i][j] == errorCode){
                printf("    .");
            }
            else 
                printf("%5i",source->table[i][j]);
        }
    } 
    printf("\n");
    
}

/*
myScanner scanByStream(FILE *fp)
{	
	if (fp == NULL) {
	    fprintf (stderr,"ERROR: Content stream is empty \n");
	    return NULL;
    }
	s->fp = fp;	

	return s;
}

myScanner scanByName(const char *filename)
{
	FILE* filePtr = fopen (filename, "r");
	//if that is a bogus argument or file is not readable
	if (filePtr == NULL){
			fprintf (stderr,"ERROR: file '%s' does not exist or not readable \n", filename);
			return NULL;
	}
	return scanByStream(filePtr);
}
*/

void clearScanner(myScanner s)
{
	// de-allocate memory
	if (s != NULL) {
		free(s);
	}
}


