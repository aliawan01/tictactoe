#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char grid[11][12] = {
	{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '\n' },
	{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\n' },
};

typedef struct {
	int input_row;
	int input_column;

	int check_row;
	int check_column;

	char* name;
	char character;
} User;

int main(void) {
	int num_grid_columns = (int)sizeof(grid[0]);
	int num_grid_rows = (int)(sizeof(grid)/sizeof(grid[0]));

	char check_character;

	User* user1 = (User*)malloc(sizeof(User));
	User* user2 = (User*)malloc(sizeof(User));

	user1->character = 'x';
	user2->character = 'o';

	user1->name = "User1";
	user2->name = "User2";

	printf("If you would like to quit the game at any time type '10'\n");

	while (true) {
		for (int y = 0; y < 2; y++) {
			User* current_user;
			if (y == 0) 
				current_user = user1;
			else
				current_user = user2;

			for (int x = 0; x < (sizeof(grid)/sizeof(grid[0])); x++) {
				if (x == 2 || x == 5 || x == 8) {
					// Checking rows
					if (grid[x][2] == current_user->character && grid[x][5] == current_user->character && grid[x][8] == current_user->character) {
						printf("\nCongratulations, %s has won the game!\n", current_user->name);
						free(user1);
						free(user2);
						exit(0);
					}

					// Checking columns
					else if (grid[2][x] == current_user->character && grid[5][x] == current_user->character && grid[8][x] == current_user->character) {
						printf("\nCongratulations, %s has won the game!\n", current_user->name);
						free(user1);
						free(user2);
						exit(0);
					}
				}
			}
			// Checking forward horizontal
			if (grid[8][2] == current_user->character && grid[5][5] == current_user->character && grid[2][8] == current_user->character) {
				printf("\nCongratulations, %s has won the game!\n", current_user->name);
				free(user1);
				free(user2);
				exit(0);
			}
			// Checking backwards horizontal
			else if (grid[2][2] == current_user->character && grid[5][5] == current_user->character && grid[8][8] == current_user->character) {
				printf("\nCongratulations, %s has won the game!\n", current_user->name);
				free(user1);
				free(user2);
				exit(0);
			}
		}

		for (int z = 0; z < 2; z++) {
			User* current_user;
			if (z == 0) 
				current_user = user1;
			else 
				current_user = user2;
				

			start_input:
			get_input_row:
			printf("%s: Type in a row (1-3): ", current_user->name);
			scanf("%d", &current_user->input_row);


			switch (current_user->input_row) {
				case 1:
					current_user->check_row = 2;
					break;
				case 2:
					current_user->check_row = 5;
					break;
				case 3:
					current_user->check_row = 8;
					break;
				case 10:
					printf("\nThank you for playing the game!\n");
					free(user1);
					free(user2);
					exit(0);
					break;

				default:
					printf("Incorrect input, please try again\n");
					goto get_input_row;

					break;
			}

			get_input_column:
			printf("%s: Type in a column (1-3): ", current_user->name);
			scanf("%d", &current_user->input_column);

			switch (current_user->input_column) {
				case 1:
					current_user->check_column = 2;
					break;
				case 2:
					current_user->check_column = 5;
					break;
				case 3:
					current_user->check_column = 8;
					break;
				case 10:
					printf("\nThank you for playing the game!\n");
					free(user1);
					free(user2);
					exit(0);
					break;

				default:
					printf("%s: Incorrect input, please try again\n", current_user->name);
					goto get_input_column;

					break;
			}

			// Checking if the position has been taken
			if (&current_user == &user1) {
				if (grid[current_user->check_row][current_user->check_column] == 'o') {
					printf("%s: That position has been taken by %s, please try again\n", current_user->name, "User2");
					goto start_input;
				}
			}
			else {
				if (grid[current_user->check_row][current_user->check_column] == 'x') {
					printf("%s: That position has been taken by %s, please try again\n", current_user->name, "User1");
					goto start_input;
				}

			}

			// Drawing the Grid
			for (int r = 0; r < num_grid_rows; r++) {
				for (int c = 0; c < num_grid_columns; c++) {
					if (&current_user == &user1) {
						check_character = 'o';
					}
					else { 
						check_character = 'x';
					}

					if (r == current_user->check_row && c == current_user->check_column && grid[r][c] != check_character) {
						grid[r][c] = current_user->character;
					}
					printf("%c", grid[r][c]);
				}
			}
		}	
	}


	return 0;
} 
