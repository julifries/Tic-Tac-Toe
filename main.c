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

// calculates new index from userindex
Index calcIndex(Index currIndex, int numIndex)
{
    currIndex.row = (int)((numIndex - 1) / WIDTH);
    currIndex.col = (int)((numIndex - 1) % WIDTH);
    return currIndex;
}

// changes the tile to a new token
void changeTile(Playfield *pf, Index tileIndex, char token)
{
    pf->pf_cells[tileIndex.row][tileIndex.col] = token;
}

Player *getNextPlayer(Player *player1, Player *player2, int counter)
{
    // if divisable by 2 return player 1, otherwise player2
    return (counter % 2 == 0) ? player1 : player2;
}

bool checkRow(Playfield *pf, char token)
{

    for (int r = 0; r < WIDTH; r++)
    {
        bool allSame = true;

        for (int c = 0; c < WIDTH; c++)
        {
            if (pf->pf_cells[r][c] != token)
            {
                allSame = false;
                break;
            }
        }
        if (allSame)
            return true;
    }
    return false;
}

bool checkCol(Playfield *pf, char token)
{
    for (int c = 0; c < WIDTH; c++)
    {
        bool allSame = true;

        for (int r = 0; r < WIDTH; r++)
        {
            if (pf->pf_cells[r][c] != token)
            {
                allSame = false;
                break;
            }
        }
        if (allSame) return true;
    }
    return false;
}

bool checkDig(Playfield *pf, char token)
{
    bool allSame = true;
    for (int i = 0; i < WIDTH; i++)
    {
        if (pf->pf_cells[i][i] != token)
        {
            allSame = false;
            break;
        }
    }
    if(allSame) return true;



    // anti-diagonal
    allSame = true;
    for (int i = 0; i < WIDTH; i++) {
        if (pf->pf_cells[i][WIDTH - 1 - i] != token) {
            allSame = false;
            break;
        }
    }// anti-diagonal
    allSame = true;
    for (int i = 0; i < WIDTH; i++) {
        if (pf->pf_cells[i][WIDTH - 1 - i] != token) {
            allSame = false;
            break;
        }
    }
    if (allSame) return true;

    return false;
    if (allSame) return true;

    return false;

}
bool isThereAWinner(Playfield *pf, char token)
{
    return checkRow(pf, token) || checkCol(pf, token) || checkDig(pf, token);
}
// PLS C gods make my code run <33

int main()
{

    // starter things
    Player player1 = {1, 'X', 0};
    Player player2 = {2, 'O', 0};
    Player *currentPlayer = &player1; // a Player pointer, may point to player 1 or player 2

    Playfield pf;
    int counter = 0;
    Index currIndex;
    int index_1d;

    printf("Welcome to Tic Tac Toe in C!");
    resetPlayfield(&pf);

    while (gameIsRunning)
    {
        currentPlayer = getNextPlayer(&player1, &player2, counter);
        printPlayfield(&pf);
        printf("It is player %d:s turn.", currentPlayer->num);
        printf(" Enter an index between 1-9:");
        scanf("%d", &index_1d);
        if (!checkIndex(index_1d))
        {
            printf(" Enter a valid index between 1-9:");
            scanf("%d", &index_1d);
        }
        currIndex = calcIndex(currIndex, index_1d);
        changeTile(&pf, currIndex, currentPlayer->token);
        if (isThereAWinner(&pf, currentPlayer->token))
        {
            printf("Player %d:s has won.", currentPlayer->num);
        }
        counter++;
    }

    return 1;
}