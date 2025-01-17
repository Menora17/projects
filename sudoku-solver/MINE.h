#define BOARD_HEIGHT		12
#define BOARD_WIDTH		12
#define WALL_SIZE		1

typedef struct {
	char mat[BOARD_HEIGHT][BOARD_HEIGHT];
	char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_HEIGHT + 2 * WALL_SIZE];
}game;
	// This general procedure initializes a matrix with a given value
void init_matrix(char* mat, int matrix_height, int matrix_width,char value);

	// This function loads the locations of the mines from the input file, setting
	// loaded mines on the board and returns how many mines were set. If the input
	// file didn’t open the function returns -1.
int  set_mines(char game_board[BOARD_HEIGHT +2 * WALL_SIZE][BOARD_WIDTH +2 * WALL_SIZE],int bombs);

	// This procedure prints the game board on the screen 
void print_board(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE]);

	// This function returns how many mines there are around a given location
int  count_mines_around(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE],int	curr_row,int curr_col);

// solve the board and copy it to the board
void solve_the_board(char mat[BOARD_HEIGHT][BOARD_WIDTH]);
// display to the user all the zeros that are in his area
void find_the_zeros(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE], char mat[BOARD_HEIGHT][BOARD_WIDTH], int	curr_row, int	curr_col);
// This general procedure initializes the board 
void init_board(game g);
// This function manage all the game
void gameManager();
// This function manage each game the player play
void gameplay();
