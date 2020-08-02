
// LEVEL 0
// New Features
//   - Groundwork (C, i/o, reading from file, strstr() func for substrings)
//   - 1D text to search & 2D list of search  keys to be found
//   - Can detect keys written from left to right

// PREREQUISITES:
// * Require constants to be big enough, so there's no need to figure out size &
//   dynamically allocate memory.
// * For best performance, make the sizes match exactly
//   (esp. because the string arrays aren't initialized)

// Disable deprecation on functions or variables deemed unsafe
// Place it at the top of the file before all `#include`s
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
//#include <string.h>  // technically need this for string funcs if using C compiler
//#include <stdlib.h>  // technically need this for system() & exit() funcs

#define NUM_OF_KEYS  6
#define MAX_KEY_LEN  10 // word to find
#define MAX_TEXT_LEN 20 // grid

#define KEYS_FILE "search1.txt"
#define TEXT_FILE "text1.txt"


int main()
{
	char search_keys[NUM_OF_KEYS][MAX_KEY_LEN];
	char text[MAX_TEXT_LEN];
	FILE *fptr = NULL;

	// ========================= ~ READ DATA FROM FILES ~ =========================

	// Read text into 1D array
	if ((fptr = fopen(TEXT_FILE, "r")) == NULL)
	{
		fprintf(stderr, "Failed to open file \"%s\"for reading\n", TEXT_FILE);
		system("pause");
		exit(1);
	}
	else
	{
		fscanf(fptr, "%s", text); // read text word (ignoring whitespace)
	}
	fclose(fptr);

	// Print out the text
	printf("\nText: %s\n", text);

	
	// Read keys into 2D array
	if ((fptr = fopen(KEYS_FILE, "r")) == NULL)
	{
		fprintf(stderr, "Failed to open file \"%s\"for reading\n", KEYS_FILE);
		system("pause");
		exit(1);
	}
	else
	{
		int i = 0;
		while ((fptr != NULL) && (i < NUM_OF_KEYS))
		{     
			fscanf(fptr, "%s", search_keys[i]); // read a word (ignoring whitespace)
			i++;
		}
	}
	fclose(fptr);

	// Print out the keys
	for (int i = 0; i < NUM_OF_KEYS; i++)
		printf("Key %d : %s\n", i+1, search_keys[i]);
	printf("\n");
	//printf("index 0 : %s\n", search_keys[0]);


	// ========================= ~ PROCESS WORD SEARCH ~ =========================

	char *pch = NULL;
	for (int i = 0; i < NUM_OF_KEYS; i++)
	{
		pch = strstr(text, search_keys[i]); // get pointer to substring if found
		if (pch)
			printf("\"%s\", Found, location %d\n", search_keys[i], pch - text);
		else
			printf("\"%s\", Not Found\n", search_keys[i]);
	}
	


	printf("\n"); system("pause"); //wait for user to exit
	//printf("\nPress the enter key to break... "); getchar(); // pause program
	return 0;
}
