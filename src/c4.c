/* 
   Kyle Smigelski
   Alexandra MacKay
*/

#include <stdio.h>
#include <stdlib.h>
#include <connect4.h>

int main(int argc, char *argv[]) {
    char *labels = "ABCDEFGHIJKLMNOP";
    int row;
    int col;
    int winLength = atoi(argv[2]);
    printf("%d", argc);

    // Parse parameter to int for row and col values, check if parameters are not entered
    if (argc == 3) {
        int parse = sscanf(argv[1], "%dx%d", &row, &col);
    } else {
        row = 6;
        col = 7;
        winLength = 4;
    }

    // Allocate space on heap for board matrix (obtained from https://c-faq.com/aryptr/dynmuldimary.html)
    int **board = malloc(row * sizeof(int *));
    for(int i = 0; i < row; i++)
        board[i] = malloc(col * sizeof(int));

    // Initialize board and print for game start
    fillBoard(row, col, board);
    printf("GAME START\nPRESS Q TO QUIT\n------------------\n");
    printBoard(row, col, board, labels);

    // Game loop
    for(int i=0; i < row*col; ++i){
        int player =  (i % 2)+1;

        // If playerTurn results in a win, end game
        if (playerTurn(row, col, board, player, winLength) == player){
            printf("Congratulations, Player %d. You win.", player);
            break;
        }
        printBoard(row, col, board, labels);
    }

    // Free memory
    for(int i = 0; i < row; i++)
        free((void *)board[i]);
    free((void *)board);
}
