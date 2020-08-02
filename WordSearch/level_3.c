
// LEVEL 3
// New Features
//   - words can be found diagonally (with given simplification of downwards)

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
#include <string.h>  // technically need this for string funcs if using C compiler (avoids warnings)
#include <stdlib.h>  // technically need this for system() & exit() funcs

#define NUM_OF_KEYS      16
#define MAX_KEY_LENGTH   4  // word to find (max len of 3, + string null terminator)
#define MAX_GRID_LENGTH  15 // (horizontal) 4x14 grid (max len of 14, + string null terminator)
#define MAX_GRID_BREADTH 4  // (vertical) 4x14 grid

#define KEYS_FILE            "search2D.txt"
#define GRID_FILE            "text2D.txt"
#define MAX_FILE_NAME_LENGTH 20

void read_data_from_files(char** search_keys, char** grid, char** output, FILE* fptr);
void process_word_search(char** search_keys, char** grid, char** output, FILE* fptr);

int main()
{
	char search_keys[NUM_OF_KEYS][MAX_KEY_LENGTH];
	char grid[MAX_GRID_BREADTH][MAX_GRID_LENGTH];
	char output[MAX_GRID_BREADTH][MAX_GRID_LENGTH];
	FILE *fptr = NULL;

	// ========================= ~ READ DATA FROM FILES ~ =========================

	read_data_from_files(search_keys, grid, output, fptr);

	// ========================= ~ PROCESS WORD SEARCH ~ =========================

	process_word_search(search_keys, grid, output, fptr);


	// ========================= ~ CREATE OUTPUT FILE NAME ~ =========================
	
	// Copy GRID_FILE until the dot. Concat "Filtered". Concat the dot & extension
	char *pch = NULL;
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
		printf("%s\n", output[i]); // Print on the screen as well
	}
	fclose(fptr);


	printf("\n"); system("pause"); //wait for user to exit
	//printf("\nPress the enter key to break... "); getchar(); // pause program
	return 0;
}







void read_data_from_files(char search_keys[NUM_OF_KEYS][MAX_KEY_LENGTH],
						  char grid[MAX_GRID_BREADTH][MAX_GRID_LENGTH],
						  char output[MAX_GRID_BREADTH][MAX_GRID_LENGTH],
						  FILE* fptr)
{
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
		printf("Key %d : %s\n", i + 1, search_keys[i]);
	printf("\n");
}




void process_word_search( char search_keys[NUM_OF_KEYS][MAX_KEY_LENGTH],
						  char grid[MAX_GRID_BREADTH][MAX_GRID_LENGTH],
						  char output[MAX_GRID_BREADTH][MAX_GRID_LENGTH],
						  FILE* fptr )
{
	char *pch = NULL;
	for (int i = 0; i < NUM_OF_KEYS; i++)
	{
		int row_index = 0, column_index = 0;
		int horizontal_found = 0; // (1 -> right, 0 -> not found, -1 -> left)
		int vertical_found = 0;   // (1 -> down,  0 -> not found, -1 -> up)
		int diagonal_found = 0;   // (1 -> down right,  0 -> not found, -1 -> down left)

		for (int j = 0; j < MAX_GRID_BREADTH; j++)
		{
			for (int k = 0; k < MAX_GRID_LENGTH; k++)
			{
				// Found 1st letter, now do checks
				if (grid[j][k] == search_keys[i][0])
				{

					int direction = 0; // specifies direction word is written in
					int count = 0; // to iterate over length of key

					// Save coordinates of the 1st letter
					row_index = j;
					column_index = k;

					// -------------------- Horizontal --------------------
					direction = 1; // forward (to the right)
					horizontal_found = direction;
					count = 1; // init to 2nd letter's index
					while (count < strlen(search_keys[i]))
					{
						// Fails if not all letters match OR grid exceeded
						if ((grid[j][k + count*direction] != search_keys[i][count]) ||
							((k + count*direction) >= MAX_GRID_LENGTH))
						{
							horizontal_found = 0;
							break;
						}
						count++;
					}

					if (horizontal_found != 1)
					{
						direction = -1; // backward (to the left)
						horizontal_found = direction;
						count = 1; // init to 2nd letter's index
						while (count < strlen(search_keys[i]))
						{
							// Fails if not all letters match OR grid exceeded
							if ((grid[j][k + count*direction] != search_keys[i][count]) ||
								((k + count*direction) < 0))
							{
								horizontal_found = 0;
								break;
							}
							count++;
						}
					}

					// If word was found (horizontally)
					if (horizontal_found != 0)
						break;


					// -------------------- Vertical --------------------
					direction = 1; // down
					vertical_found = direction;
					count = 1; // init to 2nd letter's index
					while (count < strlen(search_keys[i]))
					{
						// Fails if not all letters match OR grid exceeded
						if ((grid[j + count*direction][k] != search_keys[i][count]) ||
							((j + count*direction) >= MAX_GRID_BREADTH))
						{
							vertical_found = 0;
							break;
						}
						count++;
					}

					if (vertical_found != 1)
					{
						direction = -1; // up
						vertical_found = direction;
						count = 1; // init to 2nd letter's index
						while (count < strlen(search_keys[i]))
						{
							// Fails if not all letters match OR grid exceeded
							if ((grid[j + count*direction][k] != search_keys[i][count]) ||
								((j + count*direction) < 0))
							{
								vertical_found = 0;
								break;
							}
							count++;
						}
					}

					// If word was found (vertically)
					if (vertical_found != 0)
						break;


					// -------------------- Diagonal --------------------
					// To simplify, it's given that words are written either to the
					// left or right, but always downwards
					direction = 1; // down right
					diagonal_found = direction;
					count = 1; // init to 2nd letter's index
					while (count < strlen(search_keys[i]))
					{
						// Fails if not all letters match OR grid exceeded
						if ((grid[j + count*1][k + count*direction] != search_keys[i][count]) ||
							((j + count*1) >= MAX_GRID_BREADTH) ||
							((k + count*direction) >= MAX_GRID_LENGTH))
						{
							diagonal_found = 0;
							break;
						}
						count++;
					}

					if (diagonal_found != 1)
					{
						direction = -1; // down left
						diagonal_found = direction;
						count = 1; // init to 2nd letter's index
						while (count < strlen(search_keys[i]))
						{
							// Fails if not all letters match OR grid exceeded
							if ((grid[j + count*1][k + count*direction] != search_keys[i][count]) ||
								((j + count*1) >= MAX_GRID_BREADTH) ||
								((k + count*direction) < 0))
							{
								diagonal_found = 0;
								break;
							}
							count++;
						}
					}

					// If word was found (diagonally)
					if (diagonal_found != 0)
						break;

				}
			}

			// if one of the directions has been found, break
			if ((horizontal_found != 0) || (vertical_found != 0) || (diagonal_found != 0))
				break;

		}

		// Print out if word was found
		if (horizontal_found != 0)
			printf("\"%s\", Found, horizontally @ row %d, column %d\n", search_keys[i], row_index + 1, column_index + 1);
		else if (vertical_found != 0)
			printf("\"%s\", Found, vertically @ row %d, column %d\n", search_keys[i], row_index + 1, column_index + 1);
		else if (diagonal_found != 0)
			printf("\"%s\", Found, diagonally @ row %d, column %d\n", search_keys[i], row_index + 1, column_index + 1);


		// if one of the directions has been found, update output
		if (horizontal_found == 1) // forward
		{
			// replace the position of the words chars with dots
			for (int pos = 0; pos < strlen(search_keys[i]); pos++)
				output[row_index][column_index + pos] = '.';
		}
		else if (horizontal_found == -1) // backward
		{
			// replace the position of the words chars with dots
			for (int pos = 0; pos < strlen(search_keys[i]); pos++)
				output[row_index][column_index - pos] = '.';
		}

		else if (vertical_found == 1) // down
		{
			// replace the position of the words chars with dots
			for (int pos = 0; pos < strlen(search_keys[i]); pos++)
				output[row_index + pos][column_index] = '.';
		}
		else if (vertical_found == -1) // up
		{
			// replace the position of the words chars with dots
			for (int pos = 0; pos < strlen(search_keys[i]); pos++)
				output[row_index - pos][column_index] = '.';
		}

		else if (diagonal_found == 1) // down right
		{
			// replace the position of the words chars with dots
			for (int pos = 0; pos < strlen(search_keys[i]); pos++)
				output[row_index + pos][column_index + pos] = '.';
		}
		else if (diagonal_found == -1) // down left
		{
			// replace the position of the words chars with dots
			for (int pos = 0; pos < strlen(search_keys[i]); pos++)
				output[row_index + pos][column_index - pos] = '.';
		}

	}
}
