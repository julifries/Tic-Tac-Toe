#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 3

// some global variables

bool gameIsRunning = true;
//------------------------------

typedef struct Playfield
{

    struct Playfield *pf_ptr;
    char pf_cells[WIDTH][WIDTH];
} Playfield;

typedef struct Player
{
    int num;
    char token;
    int score;
} Player;

typedef struct Index
{
    int row;
    int col;

} Index;

// expects &pf when used, because we give the adress where the struct is
void resetPlayfield(Playfield *pf)
{
    for (int i = 0; i < WIDTH; i++)
    {

        for (int j = 0; j < WIDTH; j++)
        {
            pf->pf_cells[i][j] = '-';
        }
    }
}

// prints the playfield, nice formating
void printPlayfield(Playfield *pf)
{

    for (int i = 0; i < WIDTH; i++)
    {
        printf("\n");
        for (int j = 0; j < WIDTH; j++)
        {

            printf("%c", pf->pf_cells[i][j]);
        }
    }
    printf("\n");
}

// witchcraft method to return two values in one

// checks if a index given by player is in bounds in the playfield
bool checkIndex(int user_index)
{
    return user_index > 0 && user_index < WIDTH * WIDTH + 1;
}


//calculates new index from userindex
Index calcIndex(Index currIndex, int numIndex)
{
    currIndex.row = (int)(numIndex / WIDTH);
    currIndex.col = (int)(numIndex % WIDTH);
    return currIndex;
}


//changes the tile to a new token
void changeTile(Playfield *pf, Index tileIndex, char token)
{
    pf->pf_cells[tileIndex.row][tileIndex.col] = token;
}

// PLS C gods make my code run <33

int main()
{

    // starter things
    Player player1 = {1, 'X', 0};
    Player player2 = {2, 'O', 0};
    Player currentPlayer;

    // link player structs to itself

    Playfield pf;

    printf("Welcome to Tic Tac Toe in C!");
    resetPlayfield(&pf);

    while (gameIsRunning)
    {
        printPlayfield(&pf);
    }

    return 1;
}