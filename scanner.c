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

//length of a token's value
int bufLen = 8;

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

struct Token {
    int tokenType;
    char tokenVal[8];
    int  tokenLine;
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

void clearScanner(myScanner s)
{
	// de-allocate memory
	if (s != NULL) {
		free(s);
	}
}

myToken initToken () {
    
    myToken    t;
    // allocate memory for scanner
	t = malloc(sizeof(struct Token));
    
    return t;
}

void clearToken (myToken t)
{
	// de-allocate memory
	if (t != NULL) {
		free(t);
	}
}

int findNextState (const int currentState,const char c, int stateTable[100][100]) {
    int nextState = 0;
    int currentVal = (int) c;
    //map currentVal
    if ((currentVal>=65 && currentVal<=90) || (currentVal>=97 && currentVal<=122)){
        currentVal = 0; //map to col 0 in mapped automaton table
    }
    if (currentVal>=48 && currentVal <=57){
        currentVal = 1;
    }
    if (currentVal == 32) currentVal = 2;
    if (currentVal == 61) currentVal = 3;
    if (currentVal == 60) currentVal = 4;
    if (currentVal == 62) currentVal = 5;
    if (currentVal == 33) currentVal = 6;
    if (currentVal == 58) currentVal = 7;
    if (currentVal == 43) currentVal = 8;
    if (currentVal == 45) currentVal = 9;
    if (currentVal == 42) currentVal = 10;
    if (currentVal == 47) currentVal = 11;
    if (currentVal == 38) currentVal = 12;
    if (currentVal == 37) currentVal = 13;
    if (currentVal == 46) currentVal = 14;
    if (currentVal == 40) currentVal = 15;
    if (currentVal == 41) currentVal = 16;
    if (currentVal == 44) currentVal = 17;
    if (currentVal == 123) currentVal = 18;
    if (currentVal == 125) currentVal = 19;
    if (currentVal == 59) currentVal = 20;
    if (currentVal == 91) currentVal = 21;
    if (currentVal == 93) currentVal = 22;
    if (currentVal == 64) currentVal = 23;
    
    nextState = stateTable[currentState][currentVal];
    return nextState;
    
}

myToken getToken(myScanner s) {
    
    int currentState = 0;
    int charRead = 0;
    int line = 0;
    char c;
    char buffer[bufLen];
    int flag = 0;
    
    myToken t;
    t = initToken ();
    
    while ((charRead + 1 < bufLen) && ((c = fgetc(s->fp)) != EOF) && (flag==0)) {
        
		buffer[charRead++] = c;							// append c to buffer
		currentState = findNextState (currentState, c, s->table);
		
		if (currentState>=991 && currentState <=996) { // if a correct token is found
		    flag = 1;
		    t->tokenType = currentState;
		    strcpy(t->tokenVal, buffer);
		    t->tokenLine = line;
		    buffer[charRead] = '\0';							// terminate buffer
		}
		
        if (currentState==980) {
            fprintf (stderr,"ERROR !! \n");
            flag = 1;
		    t->tokenType = currentState;
		    strcpy(t->tokenVal, "[Error]");
		    t->tokenLine = line;
		    buffer[charRead] = '\0';							// terminate buffer
        }
	}
    
    return t;
}