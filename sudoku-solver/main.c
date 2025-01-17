#include<stdio.h>
#include<stdint.h>
#include "MINE.h"

int main() {


	gameManager();
	/*for ( i = 0; i < BOARD_WIDTH+2; i++)
	{
		g.game_board[0][i] = '#';
		g.game_board[0][BOARD_WIDTH + 1-i] = '#';
	}
	for (i = 0; i < BOARD_HEIGHT+2; i++)
	{
		g.game_board[i][0] = '#';
		g.game_board[BOARD_HEIGHT + 1 - i][0] = '#';
	}
	for ( i = 1; i < BOARD_HEIGHT+2; i++) {
		for ( j = 1; j < BOARD_WIDTH+2; j++) {
			if (j == BOARD_HEIGHT + 1) {
				g.game_board[i][BOARD_WIDTH + 1 ] = '#';
			}
			else
			{
				g.game_board[i][j] = g.mat[i - 1][j - 1];
			}
			if (i == BOARD_HEIGHT + 1) {
				g.game_board[i][j] = '#';
			}
		}
	}
	*/

	
	return 0;
}