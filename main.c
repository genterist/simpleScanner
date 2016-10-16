/*
 ============================================================================
 Name        : main.c
 Author      : NGUYEN, TAM N
 Created on  : 15OCT16
 Version     : 1
 Copyright   : (CC)
 Summary	 : all functions related to a successfully built BSTree
 Functions	 :
 Origins	 : UMSL COMPSCI 4280
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "./scanner.h";

int main(int argc, char *argv[])
{
	char *prog = argv[0]; //capture program name here

	// if user put in many arguments
	if (argc>2) {
		fprintf (stderr,"ERROR: Too many arguments !! \n");
		fprintf (stderr,"       %s [data file name] \n", prog);
	}
	
	myScanner scanIt;
	scanIt = initScanner();



	clearScanner (scanIt);
	
	return EXIT_SUCCESS;
}
