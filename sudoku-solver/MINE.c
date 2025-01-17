#include "MINE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Dir[][2] = {
	//  dr  dy
	  { -1, -1 },  // UPLEFT
	  { -1,  0 },  // UP
	  { -1,  1 },
	  {  0,  1 },
	  {  1,  1 },
	  {  1,  0 },
	  {  1, -1 },
	  {  0, -1 }  // LEFT
};




void init_matrix(char* mat, int matrix_height, int matrix_width, char value) {
    // Initiate the random number generator so that
    // the same configuration doesn't arises
    int i,j;
    srand(time(NULL));
    for (i = 0; i < matrix_height+1; i++) {
        for (j = 0; j < matrix_width+1; j++) {
            mat[i * (matrix_width+1) + j] = value;
        }
    }
    return;
}
void init_board(game* g) {
    int i, j;
    for (i = 0; i < BOARD_WIDTH + 2; i++)
    {
        
        g->game_board[0][i] = '#';
        g->game_board[0][BOARD_WIDTH + 1 - i] = '#';
    }
    for (i = 0; i < BOARD_HEIGHT + 2; i++)
    {
        g->game_board[i][0] = '#';
        g->game_board[BOARD_HEIGHT + 1 - i][0] = '#';
    }
    for (i = 1; i < BOARD_HEIGHT + 2; i++) {
        for (j = 1; j < BOARD_WIDTH + 2; j++) {
            if (j == BOARD_HEIGHT + 1) {
                g->game_board[i][BOARD_WIDTH + 1] = '#';
            }
            else
            {
                g->game_board[i][j] = g->mat[i - 1][j - 1];
            }
            if (i == BOARD_HEIGHT + 1) {
                g->game_board[i][j] = '#';
            }
        }
    }

}
int set_mines(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE],int bombs) {
    int check = 0;

    for (int i = 0; i < bombs;i++ )
    {
        int random = rand() % (BOARD_WIDTH * BOARD_WIDTH);
        int x = random / BOARD_WIDTH;
        int y = random % BOARD_WIDTH;

        // Add the mine if no mine is placed at this
        // position on the board
        if (game_board[x][y] == '-')
        {
            // Row Index of the Mine
            game_board[x][y] = '*';
            check=1;
        }
        if (check) {
            check = 0;
            i++;
        }
           
    }
    printf("\n");
    return bombs;
}

// This procedure prints the game board on the screen 
void print_board(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE]) {
    int i, j;

    printf("    ");

    for (i = 1; i < BOARD_WIDTH+2; i++)
        printf("%d ", i);

    printf("\n\n");

    for (i = 0; i < BOARD_WIDTH+2; i++)
    {
        printf("%d   ", i+1);

        for (j = 0; j < BOARD_WIDTH+2; j++)
            printf(" %c", game_board[i][j]);
        printf("\n");
    }
}

// This function returns how many mines there are around a given location
int  count_mines_around(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE], int	curr_row, int	curr_col) {
    
    int sum = 0, i;
    for (i = 0; i < 8; i++)
        if (game_board[curr_row + Dir[i][0]][curr_col + Dir[i][1]] == '*')
            sum++;

    return sum;
}
void solve_the_board(char mat[BOARD_HEIGHT+2][BOARD_WIDTH+2]) {
    int i,j;
    for ( i = 1; i < BOARD_HEIGHT+1; i++)
    {
        for ( j = 1; j < BOARD_WIDTH+1; j++)
        {
            if(mat[i][j]!='*')
                mat[i][j] = count_mines_around(mat, i, j)+'0';
        }
    }
}
void find_the_zeros(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE],char mat[BOARD_HEIGHT][BOARD_WIDTH], int	curr_row, int	curr_col) {
    int i,j;
    if (game_board[curr_row][curr_col]=='#')
        return 0;
    if (mat[curr_row - 1][curr_col - 1] == '0') {
        game_board[curr_row][curr_col] = '0';
        mat[curr_row - 1][curr_col - 1] = '#';

    }  
    else
    {
        game_board[curr_row][curr_col] = mat[curr_row-1][curr_col-1] ;
        return;
    }
    
    for (i = 0; i < sizeof(Dir) / sizeof(Dir[0]); i++)
        find_the_zeros(game_board,mat , curr_row + Dir[i][0], curr_col + Dir[i][1]);
    if (game_board[curr_row][curr_col] == '0')
        return;
    for (i = 1; i < BOARD_HEIGHT + 1; i++)
    {
        for (j = 1; j < BOARD_WIDTH + 1; j++)
        {
            if (mat[i-1][j-1] == '#')
                game_board[i][j] = '0';
        }
    }
}
void gameplay() {
    game g;

    int i, j;

    init_matrix(g.mat, 12, 12, '-');
    init_board(&g);
    int x, y;
    int bombs;
    printf("how many bombs do you want? ");
    scanf_s("%d", &bombs);
    set_mines(g.game_board,bombs);
    solve_the_board(g.game_board);
    for (i = 0; i < BOARD_HEIGHT; i++)
    {
        for (j = 0; j < BOARD_WIDTH; j++)
        {
            g.mat[i][j] = g.game_board[i + 1][j + 1];
            g.game_board[i + 1][j + 1] = '.';
        }
    }
    print_board(g.game_board);
    printf("Enter a row and a coloum: ");
    scanf_s("%d%d", &x, &y);
    while (--bombs)
    {
        if (g.mat[x - 1][y - 1] == '*') {
            printf("game over!!!\n");
            return;
        }
        else
        {

            if (g.mat[x - 1][y - 1] == '0') {
                find_the_zeros(g.game_board, g.mat, x, y);
            }
            else
                g.game_board[x][y] = g.mat[x - 1][y - 1];
        }
        print_board(g.game_board);
        scanf_s("%d %d", &x, &y);

    }
    printf("you won!!!\n");
    return;
}
void gameManager() {
    
    int answer;
    printf("do you want to play? ");
    scanf_s("%d", &answer);
    while (answer)
    {
        gameplay();
        printf("do you want to play again?");
        scanf_s("%d", &answer);
    }
    printf("ok bye!");
    return;
    
    
    
   


    
}




