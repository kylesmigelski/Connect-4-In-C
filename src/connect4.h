/*
   Kyle Smigelski
   Alexandra MacKay
*/
#ifndef CONNECT4_H
#define CONNECT4_H
#include <stdio.h>

int x_in_a_row(int x, int length, char array[]);
void fillBoard(int row, int col, int **board);
void printBoard(int row, int col, int **board, char *labels);
int c_to_n(char c);
int validInput(int row, int col, int **board, int selection);
int playerTurn(int row, int col, int **board, int player, int winLength);
int board_to_array(int **board, int selection, int row, int col, int rowSelection, int winLength);

#endif