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

#include "buildTree.h"
#include "traversals.h"

int main(int argc, char *argv[])
{
	char *prog = argv[0]; //capture program name here
	char theFileName[256];
	char theName[256];

	//init tree
	Treeptr myBNTree;
	myBNTree = NULL;

	// if user put in many arguments
	if (argc>2) {
		fprintf (stderr,"ERROR: Too many arguments !! \n");
		fprintf (stderr,"       %s [data file name] \n", prog);
	}
	else {
		// if a data file argument is specified
		if (argv[1]!=NULL) {
		    
		    //construct file name
		    strncpy(theFileName, argv[1], sizeof(theName));

			FILE* filePtr = fopen (theFileName, "r");

			//if that is a bogus argument or file is not readable
			if (filePtr == NULL){
				fprintf (stderr,"ERROR: file '%s' does not exist or not readable \n", argv[1]);
			}
			//if file is readable
			else {
				char i = "";
				int nodes = 0;
				int flag = 0; // value of 1 means raised flag

				while (flag==0 && !feof (filePtr))
				{
					myBNTree= buildTree(myBNTree,(char) i, NULL);
					nodes++;
					if (fscanf (filePtr, "%c", &i) == 0){
						fprintf (stderr,"ERROR: Invalid value read !! \n");
						flag = 1;
					}
					fprintf (stderr,".");
				}

				fclose (filePtr);
				fprintf (stderr,"\n %d character(s) read from %s \n", nodes, theFileName);
			}

		}
		// if data file argument is not listed
		// we will take input from keyboard or a redirection
		else {
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
					myBNTree= buildTree(myBNTree,(int) i, NULL);
					nodes++;
				}
			}
			fprintf (stderr,"\n %d integer(s) were added to the tree. \n", nodes);

		}

		//Traverse functions :: output to screen if no output file name specified
		sprintf(theFileName, "%s.inorder", theName);
		TravInOrder(myBNTree, 0, theFileName);
		sprintf(theFileName, "%s.preorder", theName);
		TravPreOrder(myBNTree, 0, theFileName);
		sprintf(theFileName,"%s.postorder", theName);
		TravPostOrder(myBNTree, 0, theFileName);
	}
	return EXIT_SUCCESS;
}
