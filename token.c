/*
 ============================================================================
 Name        : token.c
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

#include "./token.h"

//configurations
int bufLen = 9;
int line = 1;
int lineFlag = 0;

struct Token {
    int tokenType;
    char tokenVal[8];
    int  tokenLine;
};

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
    //printf ("Next state is : %d \n", nextState);
    return nextState;
    
}

myToken getToken(myScanner s) {
    
    int currentState = 0;
    int charRead = 0;
    char c;
    char buffer[bufLen];
    int flag = 0;
    
    myToken t;
    t = initToken ();
    
    c = fgetc(s->fp);
    
    while (flag==0) {
        
        if (charRead + 1 > bufLen) {
            flag = 1;
            fprintf (stderr,"ERROR: Token name exceeds %d characters!! \n", bufLen);
            }                     //concat all characters beyond buffer
        if (c == '\n') {                                        //in case of a new line 
            lineFlag = 1;
            c = ' ';                                            //treat it as a white space
        }
        
        if (c == EOF) {
            //fprintf (stderr,"End of file reached. \n");
            c = ' ';                                           //treat it as a white space
            flag = 1;                                          //treat it as a white space
        }
        
		currentState = findNextState (currentState, c, s->table);
		
		if (currentState>=991 && currentState <=999) {            // if a correct token is found
		    flag = 1;
		    t->tokenType = currentState;
		    strcpy(t->tokenVal, buffer);
		    t->tokenLine = line;
		    memset(&buffer[0], 0, sizeof(buffer));                // clearing the buffer
		    line = line + lineFlag;
            lineFlag = 0;
            ungetc(c, s->fp);                                     // step back one character
		}
		else if (currentState==980) {
            fprintf (stderr,"ERROR !! \n");
            flag = 1;
		    t->tokenType = currentState;
		    strcpy(t->tokenVal, "[Error]");
		    t->tokenLine = line;
		    fprintf (stderr,"ERROR: !! \n");
		    memset(&buffer[0], 0, sizeof(buffer));                // clearing the buffer
        }
        else {
            buffer[charRead++] = c;							      // append c to buffer
            c = fgetc(s->fp);
            
        }

	}
    
    
    return t;
}

int hasTokenError (myToken t) {
    if (strcmp(t->tokenVal, "[Error]") == 0) return 1;
    if (strcmp(t->tokenVal, "") == 0) return 1;
    return 0;
}


void printToken (myToken t) {
    char tokenName[50];
    int x = t->tokenType;
    if (x==idCode) strcpy(tokenName,"Identifier");
    else if (x==relCode) strcpy(tokenName,"Relational operator");
    else if (x==otherCode) strcpy(tokenName,"Other operator");
    else if (x==delimCode) strcpy(tokenName,"Delimiter");
    else if (x==intCode) strcpy(tokenName,"Integer");
    else if (x==comCode) strcpy(tokenName,"Comment");
    else strcpy(tokenName,"[ERROR]");
    
    printf("\{ %s , %s , %d }\n",tokenName, t->tokenVal, t->tokenLine);
    memset(&tokenName[0], 0, sizeof(tokenName)); 
}

