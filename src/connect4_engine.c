/* 
   Kyle Smigelski
   Alexandra MacKay
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "connect4.h"

/*********************************
 * Loops over an array and checks if there is 'winLenth' values in a row for player 1 and player 2.
 * @param winLength
 * @param arrayLength
 * @param array
 * @retuvalrn
 */
int x_in_a_row(int winLength, int arrayLength, char array[]) {
    int player1=0;
    int player2=0;
    for(int i = 0; i < arrayLength; i++){

        // If value at is 1, increment player1, reset player2, and check for winLength
        if (array[i] == 1) {
            player1++;
            player2=0;
            if (player1 == winLength)
                return 1;
        }
        else if (array[i] == 2){
            player2++;
            player1=0;
            if (player2 == winLength)
                return 2;
        }

        // If value is -1, reset counters
        else {
            player1=0;
            player2=0;
        }
    }
    return 0;
}

/*********************************
 * Prints board
 * @param row
 * @param col
 * @param board
 * @param labels
 */
void printBoard(int row, int col, int **board, char *labels) {
    int i, j;

    // Print letter labels
    for (i = 0; i < col; i++) {
        printf("%c  ", labels[i]);
    }
    printf("\n");

    // Print board in reverse order
    for (i = (row-1); i >= 0; i--) {
        for (j = 0; j < col; j++) {

            // If spot is not empty, print its value. Else, print "."
            if (board[i][j] != -1) {
                printf("%d  ", board[i][j]);
            } else {
                printf(".  ");
            }
            if (j == (col - 1)) {
                printf("\n");
            }
        }
    }
}

/*********************************
 * Fills board with -1
 */
void fillBoard(int row, int col, int **board) {
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            board[i][j] = -1;
}

// Character to number conversion method obtained from https://stackoverflow.com/questions/1469711/converting-letters-to-numbers-in-c?rq=1
int c_to_n(char c)
{
    int n = -1;
    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p = strchr(alphabet, toupper((unsigned char)c));

    if (p)
    {
        n = p - alphabet;
    }

    return n;
}

/**********************************************
 * If the players input is negative, off the board, or the column if full, return false.
 * @param row
 * @param col
 * @param board
 * @param selection
 * @return
 */
int validInput(int row, int col, int **board, int selection){
    int topRow = board[row-1][selection];
    if (selection >= col || selection < 0 || topRow != -1) {
        return false;
    }
    return true;
}

/**********************************************
 * playerTurn retrieves user input, adds it to the board, and returns a value for
 * player win.
 * @param row
 * @param col
 * @param board
 * @param player
 * @param winLength
 * @return
 */
int playerTurn(int row, int col, int **board, int player, int winLength) {
    int valid = true;
    int selection;
    int i;

    // While loop checks if input is valid
    while(valid == true) {
        char letter;

        // Retrieve user input
        printf("\nPlayer %d, please enter a column: \n", player);
        scanf(" %c", &letter);

        // If player enters q, quit
        if (letter == 'q' || letter == 'Q') {
            printf("Goodbye.\n");
            exit(0);
        }
        selection = c_to_n(letter);

        // Check input
        if (validInput(row, col, board, selection) != 0)
            valid = false;
        else
            printf("Input is not on the board. Please try again.\n");
    }

    // Add players selection to board
    int rowSelection;
    for (i = 0; i < row; i++) {

        // if selection is empty, place token and stop loop
        if (board[i][selection] == -1) {
            board[i][selection] = player;
            break;
        }
    }
    rowSelection = i;

    // Return winner value by calling board_to_array
    return board_to_array(board, selection, row, col, rowSelection, winLength);
}

/************************************
 * Copies rows, columns, and diagonals to arrays and passes them to x_in_a_row to check for a win
 * @param board
 * @param colSelection
 * @param row
 * @param col
 * @param rowSelection
 * @param winLength
 * @return
 */
int board_to_array(int **board, int colSelection, int row, int col, int rowSelection, int winLength){
    char array[col+row+2];
    int i, j;

    // Copy column
    for (i = 0; i < row; i++) {
        array[i] = board[i][colSelection];
    }
    array[row+1] = 0;

    // Copy row
    for(j = 0; j < col; j++){
        array[j+row+1] = board[rowSelection][j];
    }
    array[col+1+j] = 0;

    // Find diagonal direction array lengths
    int upRightSize=0;
    int upLeftSize=0;
    int downRightSize=0;
    int downLeftSize=0;
    for (int i = 0; i < winLength*4; i++){
        if (((rowSelection - i) > 0) && ((colSelection + i) < col-1))
            upRightSize++;
        if ((rowSelection - i) > 0 && (colSelection - i) > 0)
            upLeftSize++;
        if ((rowSelection + i) < row-1 && (colSelection - i) > 0)
            downLeftSize++;
        if ((rowSelection + i) < row-1 && (colSelection + i) < col-1)
            downRightSize++;
    }

    // Initialize up and down diagonal arrays
    char down[downRightSize+upLeftSize+1];
    char up[upRightSize+downLeftSize+1];

    // Populate "up" diagonal array with corresponding values
    int c = 1;
    for (int i = 0; i < sizeof(up); i++){

        // Starting on one end, take values from "down left" diagonal until reaching the player selected row/col
        if (i < downLeftSize+1){
            up[i] = board[(rowSelection + downLeftSize) - i][(colSelection - downLeftSize) + i];

        // Starting one above player selected location, take values from "up right" diagonal
        } else {
            up[i] = board[rowSelection - c][colSelection + c];
            c++;
        }
    }

    // Populate "down" diagonal array with corresponding values
    int n = 1;
    for (int i = 0; i < sizeof(down); i++){
        if (i < upLeftSize+1){
            down[i] = board[(rowSelection - upLeftSize) + i][(colSelection - upLeftSize) + i];
        } else {
            down[i] = board[rowSelection + n][colSelection + n];
            n++;
        }
    }

    // Store win states for each direction by calling x_in_a_row
    int upWin = x_in_a_row(winLength, sizeof(up), up);
    int downWin = x_in_a_row(winLength, sizeof(down), down);
    int rowAncColWin = x_in_a_row(winLength, sizeof(array), array);

    // Put values into an array, loop and return the winner
    char winners[3] = {upWin, downWin, rowAncColWin};
    for (int i = 0; i < 3; i++) {
        if (winners[i] != 0) {
            return winners[i];
        }
    }
    return 0;
}



