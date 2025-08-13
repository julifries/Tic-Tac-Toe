#include <stdio.h>
#define WIDTH 3

typedef struct Playfield
{

    struct Playfield *pf_ptr;
    char pf_cells[WIDTH][WIDTH];
} Playfield;

typedef struct Player
{
    struct Player *p_ptr;
    char value;
} Player;

typedef struct Index{
    struct Index *i_ptr;
    int row;
    int col;

}Index;



//expects &pf when used, because we give the adress where the struct is
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

            printf("%c",pf->pf_cells[i][j]);
        }
    }
     printf("\n");
}

* Index getIndexValues (int num){
   Index *index_ptr = malloc(sizeof(Index));
   index_ptr -> row =(int)(num/WIDTH);
   index_ptr->col= num%WIDTH;
}








int main()
{
    printf("Welcome to Tic Tac Toe in C!");
    Playfield pf;
    resetPlayfield(&pf);
    printPlayfield(&pf); 
    return 1;
  
}