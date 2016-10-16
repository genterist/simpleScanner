/*
 ============================================================================
 Name        : main.c
 Author      : NGUYEN, TAM N
 Created on  : 09SEP16
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

			FILE* filePtr = fopen (argv[1], "r");

			//if that is a bogus argument or file is not readable
			if (filePtr == NULL){
				fprintf (stderr,"ERROR: file '%s' does not exist or not readable \n", argv[1]);
			}
			//if file is readable
			else {
				strncpy(theName, argv[1], sizeof(theName));
				int i = 0;
				int nodes = 0;
				int flag = 0; // value of 1 means raised flag

				if (fscanf (filePtr, "%d", &i) == 0){
					fprintf (stderr,"ERROR: Invalid value read !! \n");
					fprintf (stderr,"       Program terminated \n");
					flag = 1;
				}

				while (flag==0 && !feof (filePtr))
				{
					myBNTree= buildTree(myBNTree,(int) i, NULL);
					nodes++;
					if (fscanf (filePtr, "%d", &i) == 0){
						fprintf (stderr,"ERROR: Invalid value read !! \n");
						flag = 1;
					}
					fprintf (stderr,".");
				}

				fclose (filePtr);
				fprintf (stderr,"\n %d integer(s) read from %s \n", nodes, argv[1]);
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
