
// LEVEL 1
// New Features
//   - Using 2D grid (added & renamed some constants)
//   - Writes the output as a grid in a new file
//   - Can now detect keys written backwards
//   - *removed saying when words weren't found
//   - *detects overlapping words

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
//#include <string.h>  // technically need this for string funcs if using C compiler (avoids warnings)
//#include <stdlib.h>  // technically need this for system() & exit() funcs

#define NUM_OF_KEYS      16
#define MAX_KEY_LENGTH   4  // word to find (max len of 3, + string null terminator)
#define MAX_GRID_LENGTH  15 // 4x14 grid (max len of 14, + string null terminator)
#define MAX_GRID_BREADTH 4  // 4x14 grid

#define KEYS_FILE            "search2D.txt"
#define GRID_FILE            "text2D.txt"
#define MAX_FILE_NAME_LENGTH 20


int main()
{
	char search_keys[NUM_OF_KEYS][MAX_KEY_LENGTH];
	char grid[MAX_GRID_BREADTH][MAX_GRID_LENGTH];
	char output[MAX_GRID_BREADTH][MAX_GRID_LENGTH];
	FILE *fptr = NULL;

	// ========================= ~ READ DATA FROM FILES ~ =========================

	// Read grid into 2D array (both original grid & output)
	if ((fptr = fopen(GRID_FILE, "r")) == NULL)
	{
		fprintf(stderr, "Failed to open file \"%s\"for reading\n", GRID_FILE);
		system("pause");
		exit(1);
	}
	else
	{
		int i = 0;
		while ((fptr != NULL) && (i < MAX_GRID_BREADTH))
		{
			fscanf(fptr, "%s", grid[i]); // read a word (ignoring whitespace)
			strcpy(output[i], grid[i]); // output[i] = grid[i]
			i++;
		}
	}
	fclose(fptr);

	// Print out the grid
	printf("Grid:\n");
	for (int i = 0; i < MAX_GRID_BREADTH; i++)
		printf("%s\n", grid[i]);
	printf("\n");

	
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


	// ========================= ~ PROCESS WORD SEARCH ~ =========================

	char *pch = NULL;
	for (int i = 0; i < NUM_OF_KEYS; i++)
	{
		
		int is_reversed = 0;
		for (int j = 0; j < MAX_GRID_BREADTH; j++)
		{
			pch = strstr(grid[j], search_keys[i]); // get pointer to substring if found
			
			if (!pch) // if not found, reverse the string variable
			{
				pch = strstr( grid[j], strrev(search_keys[i]) );
				is_reversed = 1 - is_reversed;
			}

			if (pch) // if word is found in one of the rows of the grid..
			{
				// replace the position of the words chars with dots
				for (int pos = 0; pos < strlen(search_keys[i]); pos++)
				{
					output[j][(pch - grid[j]) + pos] = '.';
				}
				if (is_reversed == 1) strrev(search_keys[i]); // reverse back if needed
				printf("\"%s\", Found, line %d, location %d\n", search_keys[i], j + 1, pch - grid[j]);
				break; // done with this word
			}
		}

	}


	// ========================= ~ CREATE OUTPUT FILE NAME ~ =========================
	
	// Copy GRID_FILE until the dot. Concat "Filtered". Concat the dot & extension
	char output_file_name[MAX_FILE_NAME_LENGTH];
	char grid_file_name[MAX_FILE_NAME_LENGTH];

	strcpy(grid_file_name, GRID_FILE);
	pch = strstr(grid_file_name, "."); // get pointer to substring of the extension 
	// copy up to the number of characters before the extension
	strncpy(output_file_name, grid_file_name, (pch - grid_file_name));
	output_file_name[(pch - grid_file_name)] = '\0'; // terminate so taken as string
	// insert "Filtered" into name of output file
	sprintf(output_file_name, "%sFiltered%s", output_file_name, pch);
	
	// Print output file name to make sure it's correct
	printf("\nOutput file name: %s\n", output_file_name);


	// ========================= ~ WRITE OUTPUT TO FILE ~ =========================

	fptr = fopen(output_file_name, "w");
	for (int i = 0; i < MAX_GRID_BREADTH; i++) {
		fprintf(fptr, "%s\n", output[i]);
	}
	fclose(fptr);


	printf("\n"); system("pause"); //wait for user to exit
	//printf("\nPress the enter key to break... "); getchar(); // pause program
	return 0;
}

