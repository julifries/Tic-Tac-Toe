#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 3

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


// checks if a index given by player is in bounds in the playfield

// calculates new index from userindex, can return two indexes
Index calcIndex(int numIndex)
{
    Index currIndex;
    currIndex.row = (int)((numIndex - 1) / WIDTH);
    currIndex.col = (int)((numIndex - 1) % WIDTH);
    return currIndex;
}

bool checkIndex(Playfield *pf, int user_index)
{
    Index tmp_index = calcIndex(user_index); // calculate index

    return user_index > 0 && user_index < WIDTH * WIDTH + 1 && pf->pf_cells[tmp_index.row][tmp_index.col] == '-';
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
        if (allSame)
            return true;
    }
    return false;
}

bool checkDig(Playfield *pf, char token)
{
    //ordinary diagonal
    bool allSame = true;
    for (int i = 0; i < WIDTH; i++)
    {
        if (pf->pf_cells[i][i] != token)
        {
            allSame = false;
            break;
        }
    }
    if (allSame)
        return true;

    // anti-diagonal
    allSame = true;
    for (int i = 0; i < WIDTH; i++)
    {
        if (pf->pf_cells[i][WIDTH - 1 - i] != token)
        {
            allSame = false;
            break;
        }
    }
    if (allSame)
        return true;

    return false;
    if (allSame)
        return true;

    return false;
}

//check if there is a winner, row-wise, column-wise or diagonal/antidiagonal
bool isThereAWinner(Playfield *pf, char token)
{
    return checkRow(pf, token) || checkCol(pf, token) || checkDig(pf, token);
}


int main()
{

    //initilize two players
    Player player1 = {1, 'X', 0};
    Player player2 = {2, 'O', 0};
    Player *currentPlayer = &player1; // a Player pointer, may point to player 1 or player 2

    Playfield pf; //create a playfield struct
    int counter = 0; //counter to track whose turn it is
    Index currIndex; //Index to handle 1D -> 2D
    int index_1d; //index in 1D
    printf("Welcome to Tic Tac Toe in C!");
    resetPlayfield(&pf); //reset playfield
    char quit_input; //used for quitting game

    while (gameIsRunning)
    {
        printPlayfield(&pf); //print playfield
        //check if there is a winner
        if (isThereAWinner(&pf, currentPlayer->token))
        {
            printf("Player %d has won. Press Q to quit", currentPlayer->num);
            scanf("%c", &quit_input);
            if (quit_input == 'Q')
            {
                gameIsRunning == false;
            }
            //start a new game and add score to currentPlayer
            resetPlayfield(&pf);
            currentPlayer->score++;
             //print points
            printf("\n Player 1 has %d points, Player 2 has %d points",player1.score, player2.score);
        }

        //get next player
        currentPlayer = getNextPlayer(&player1, &player2, counter);

        printf("\nIt is player %d:s turn.", currentPlayer->num);
        printf("Enter an index you want to mark in the playfield:");
        scanf("%d", &index_1d);
        //So you cannot cheat
        if (!checkIndex(&pf, index_1d))
        {
            printf("Enter a valid index! You are either trying to cheat or not in bounds.");
            scanf("%d", &index_1d);
        }
        //calculate the index
        currIndex = calcIndex(index_1d);
        //change the tile
        changeTile(&pf, currIndex, currentPlayer->token);

        counter++; //add counter
    }

    return 1; //C stuff
}