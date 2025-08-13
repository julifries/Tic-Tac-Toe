#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 3


int counter_turns=0;
int current_player=1;
bool gameIsRunning=true;

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
    struct Player *p_ptr;
} Player;

typedef struct Index
{
    struct Index *i_ptr;
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
Index *getIndexValues(int num)
{
    Index *index_ptr = malloc(sizeof(Index)); // memory allocate
    index_ptr->row = (int)((num-1) / WIDTH);
    index_ptr->col = (num-1) % WIDTH;
}


//checks if a index given by player is in bounds in our fixed array
bool checkIndex(int user_index){
    //values 0<user_index<10
    return user_index>0 &user_index <WIDTH*WIDTH+1;

}


//changes a tile to a new value
void changeTile(Playfield *pf, Index *newIndex, char token)
{
pf->pf_cells[newIndex->row][newIndex->col]=token;

}

int playerTurn(int counter_turns){
    if(counter_turns%2){
        return 1;
    }
    else{
        return 2;
    }
}


bool checkTile(Playfield *pf,Index *index){
    return pf->pf_cells[index->row][index->col]=='-';
    /*
        if return true:
            tile not marked - can put token there
        if return false:
            tile is marked - cannot put token there
    
    */

}







int main()
{

    //starter things
    Player player1={1,'X',0,NULL};
    Player player2={2,'O',0,NULL};


    //link player structs to itself
    player1.p_ptr=&player1;
    player2.p_ptr=&player2;


    






    printf("Welcome to Tic Tac Toe in C!");
    Playfield pf;
    resetPlayfield(&pf);
    printPlayfield(&pf);
    return 1;
}