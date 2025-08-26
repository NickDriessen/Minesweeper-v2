#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "header.h"

int main()
{
    char answer[20];
    int board_option = 0;
    
    printf("What size board do you want?\n");
    printf("Small\t(5X5)\n");
    printf("Medium\t(8X8)\n");
    printf("Large\t(15X15)\n");

    while (board_option == 0){ //Scans for the answer and keeps looping untill its one of the options.
        printf("Input: ");
        scanf("%s", &answer);

        for (int i = 0; i < strlen(answer); i++)
            answer[i] = tolower(answer[i]);
        
        if (stricmp(answer, "small")==0) //Makes a 5x5 board
            board_option = SMALL;

        else if (stricmp(answer, "medium")==0) //Makes a 8x8 board
            board_option = MEDIUM;

        else if (stricmp(answer, "large")==0) //Makes a 15x15 board
            board_option = LARGE;

        else
            printf("\"%s\" is not a valid option, try again.\n", answer);
    }

    int real_board[15][15] = {0}; //Makes a interger 2d array and sets them all to 0
    char visual_board[15][15]; //Makes a character 2d array

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            visual_board[i][j] = '?'; //Makes it so all characters in the 2d array are set to ?

    int bombs = 0;

    make_board(board_option, real_board); //Makes the board with all the bomb locations and all the numbers

    print_board(board_option, visual_board); //Prints the board with all the ?

    do
    {
        printf("Do you want to place a flag(f) or reveal(r)?\n");
        printf("Input: ");
        scanf("%s", answer);

        if (strcmp(answer, "flag")==0 || strcmp(answer, "f")==0) //Compares the answer to the word flag or just f
            flag(board_option, visual_board);

        else if(strcmp(answer, "reveal")==0 || strcmp(answer, "r")==0) //Compares the answer to the word reveal or just r
            ask_reveal(board_option, visual_board, real_board);

        else
            printf("not a valid option try again\n"); //If you dont type any of the options it wil just print the board and repeat the question.
    
        print_board(board_option, visual_board);

    }while (win_check(board_option, visual_board, real_board) == 1); //looks if there are no safe spaces te reveal.

    printf("You win!\n"); //If all the safe spaces are revealed you will exit the loop and win the game.
    printf("Press enter to exit.\n");
    getchar();
    getchar();

    return 0;
}

void make_board(int board_option, int real_board[15][15]) //Where the board with the bombs gets made
{
    srand(time(NULL));//Makes it posible te create "random" numbers
    
    for (int i = 0; i < board_option; i++)
    {
        for (int j = 0; j < board_option; j++)
        {
            int bomb = rand() % 4; //Creates a random number between 0 and 3
            if (bomb == 1) //If the number is 1 it wil place a bomb
            {
                real_board[i][j] = BOMB;
            }
        }
    }
    for (int i = 0; i < board_option; i++)
    {
        for (int j = 0; j < board_option; j++)
        {
            if (real_board[i][j] == 0) //chack if its a 0 and not a bomb
            {
                int numb = 0;
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (real_board[k + i - 1][l + j - 1] == BOMB) //After all the bombs are placed this wil check if the 0 is surrounded with bombs and become the number of bombs around
                            numb++;
                    }
                }
            real_board[i][j] = numb; //Places the right number in the right position
            }
            //printf("%2d ", real_board[i][j]); //To print the board with the answers
        }
    //printf("\n");
    }
//printf("\n\n");
}

void print_board(int board_option, char visual_board[15][15]) //Where the board for the player gets made
{
    int y = 1;
    int x = 1;
    printf("\n");
    for (int i = 0; i < board_option; i++) //Places the /\/\/\/\ part
    {
        printf("/\\");
    }

    printf("Minesweeper"); //Places the Minesweeper

    for (int i = 0; i < board_option; i++) //Places the other side of the /\/\/\/\/\ part
    {
        printf("/\\");
    }
    
    printf("\n\n\t");

    for (int i = 0; i < board_option; i++) //Places the numbers in the x axis
    {
        printf("%3d ", x);
        x++;
    }
    printf("\n\n");
    
    for (int i = 0; i < board_option; i++)
    {
        printf("%d \t|", y); //Places the number in the y axis
        y++;
        for (int j = 0; j < board_option; j++)
        {
            printf(" %c |", visual_board[i][j]); //Places the rest of the board
        }

    printf("\n");
    }
}

void flag(int board_option, char visual_board[15][15]) //For placing the flag
{
    int x, y = 0;
    do{
        
        printf("Where do you want a flag? x/y\n");
        printf("(choose the coordinates of a flag to remove it! x/y)\n");
        printf("Input: ");
        scanf("%d %d", &x, &y); //Scans for the x and y coordinates

        if (x > board_option || x <= 0 || y > board_option || y <= 0) //Checks if the cordinates are possible
        {
            printf("invalid option try again.\n"); 
            x, y = 0; //Sets the answers back to 0 to prevent infinite looping
        }

    } while (x > board_option || y > board_option || x <= 0 || y <= 0); //Loops back to the question if not valid

    --x; //Sets the x and y 1 lower for the array
    --y;

    if (visual_board[y][x] == '?') //If the space is not yet revealed you can place a flage(!)
        visual_board[y][x] = '!';
    else if (visual_board[y][x] == '!') //If the space is already a flag(!) you can change it back to a ?
        visual_board[y][x] = '?';
    else
        printf("flag can't be placed there\n"); //If the space is already revealed it want place a flag
}

void ask_reveal(int board_option, char visual_board[15][15], int real_board[15][15]) //For revealing spaces
{
    int x, y = 0;
    do{
        
        printf("What space do you want to reveal? x/y\n");
        printf("Input: ");
        scanf("%d %d", &x, &y); //Also scans for the x and y coordinates

        if (x > board_option || x <= 0 || y > board_option || y <= 0) //Checks if the option is on the board
        {
            printf("invalid option, try again.\n");
            x, y = 0;
        }

    } while (x > board_option || y > board_option || x <= 0 || y <= 0); //If the option is not on the board it wil ask again

    --x; //Sets the x and y 1 lower for the array
    --y;
    
    if (real_board[y][x] == BOMB) //If you ask to reveal a bomb you lose the game
    {
        printf("You hit a bomb. Game over.\n");
        printf("press enter to exit.\n");
        getchar();
        getchar();
        exit(1);
    }
    else
    {
        reveal(visual_board, real_board, x, y, board_option);
    }
}

int reveal(char visual_board[15][15], int real_board[15][15], int x, int y, int board_option) //Where the number get revealed to the player
{
    char number_char[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //For making the int a char

    if (visual_board[y][x] != '?') //For when you dont ask to reveal a ? it wont do anything
        return 0;

    visual_board[y][x] = number_char[real_board[y][x]]; //sets the number from the real board to the visual board

    if (real_board[y][x] == 0) //If the numer is a 0 it wil do a flud where it wil reveal all the number next to the 0's
    {    
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i + y >= 0 && j + x >= 0 && i + y < board_option && j + x < board_option)
                {
                    if (visual_board[i + y][j + x] == '?') //Checks if it a ? so it wont loop forever
                    {
                        int next1 = j+x;
                        int next2 = i+y;
                        reveal(visual_board, real_board, next1, next2, board_option); //Sends the new cordinates of the numbers that need to be revealed
                    }
                }
            }
        }
    }
}

int win_check(int board_option, char visual_board[15][15], int real_board[15][15]) //To check if you win or not
{
    int undiscovered_safe_space = 0;

    for (int i = 0; i < board_option; i++)
        for (int j = 0; j < board_option; j++)
            if ((visual_board[i][j] == '?' || visual_board[i][j] == '!') && real_board[i][j] != BOMB) //Checks if there are still some undiscovered safe spaces
                undiscovered_safe_space++;

    if (undiscovered_safe_space == 0) //When you revealed all safe spaces it will send a 1 so the code knows you win
        return 0;
    else
        return 1;
}