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

int main(int argc, char *argv[])
{
	char *prog = argv[0]; //capture program name here

	// if user put in many arguments
	if (argc>2) {
		fprintf (stderr,"ERROR: Too many arguments !! \n");
		fprintf (stderr,"       %s [data file name] \n", prog);
	}
	else {
		// if a data file argument is specified
		if (argv[1]!=NULL) {
		    

		}
		// if data file argument is not listed
		// we will take input from keyboard or a redirection
		else {
		    char theName[256];
			int i = 0;
			int nodes = 0;
			int flag = 0;  // value of 1 is raised
			strncpy(theName,"out", sizeof(theName));
			while (flag == 0) {
				if (scanf("%d", &i)<=0) { //0: for values other than int, -1: for EOF
					fprintf (stderr,"NOTICE: Invalid value or EOF encountered !! \n");
					flag = 1;
				}
				if (flag != 1)
				{
//string recording here
					nodes++;  //keep statistic of how many characters read
				}
			}
			fprintf (stderr,"\n %d character(s) were read. \n", nodes);

		}

	}
	return EXIT_SUCCESS;
}
