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

#ifndef _TOKEN_H_
#define _TOKEN_H_

typedef struct Token *myToken;

#include <stdio.h>
#include "./scanner.h"

//configuration : token codes
#define errorCode (980)

#define idCode (991)
#define relCode (992)
#define otherCode (993)
#define delimCode (994)
#define intCode (995)
#define comCode (996)

void printToken (myToken t);
myToken getToken(myScanner s);
int hasTokenError (myToken t); 

#endif