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
    printf("Meduim\t(8X8)\n");
    printf("Large\t(15X15)\n");

    while (board_option == 0){
        printf("input: ");
        scanf("%s", &answer);

        for (int i = 0; i < strlen(answer); i++)
            answer[i] = tolower(answer[i]);
        
        if (stricmp(answer, "small")==0)
            board_option = SMALL;

        else if (stricmp(answer, "meduim")==0)
            board_option = MEDIUM;

        else if (stricmp(answer, "large")==0)
            board_option = LARGE;

        else
            printf("\"%s\" is not a valid option try again.\n", answer);
    }

    int real_board[15][15] = {0};
    char visual_board[15][15];

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            visual_board[i][j] = '?';

    int bombs = 0;

    make_board(board_option, real_board);

    print_board(board_option, visual_board);

    do
    {
        printf("Do you want to place a flag(f) or reveal(r)?\n");
        printf("input: ");
        scanf("%s", answer);

        if (strcmp(answer, "flag")==0 || strcmp(answer, "f")==0)
            flag(board_option, visual_board);

        else if(strcmp(answer, "reveal")==0 || strcmp(answer, "r")==0)
            ask_reveal(board_option, visual_board, real_board);

        else
            printf("not a valid option try again\n");
    
        print_board(board_option, visual_board);

    }while (win_check(board_option, visual_board, real_board) == 1);

    printf("you win!\n");
    printf("press enter to exit.\n");
    getchar();
    getchar();

    return 0;
}

void make_board(int board_option, int real_board[15][15])
{
    srand(time(NULL));
    
    for (int i = 0; i < board_option; i++)
    {
        for (int j = 0; j < board_option; j++)
        {
            int bomb = rand() % 4;
            if (bomb == 1)
            {
                real_board[i][j] = BOMB;
            }
        }
    }
    for (int i = 0; i < board_option; i++)
    {
        for (int j = 0; j < board_option; j++)
        {
            if (real_board[i][j] == 0)
            {
                int numb = 0;
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (real_board[k + i - 1][l + j - 1] == -1)
                            numb++;
                    }
                }
            real_board[i][j] = numb;
            }
            printf("%2d ", real_board[i][j]);
        }
    printf("\n");
    }
printf("\n\n");
}

void print_board(int board_option, char visual_board[15][15])
{
    int y = 1;
    int x = 1;
    printf("\n");
    for (int i = 0; i < board_option; i++)
    {
        printf("/\\");
    }

    printf("Minesweeper");

    for (int i = 0; i < board_option; i++)
    {
        printf("/\\");
    }
    
    printf("\n\n\t");
    for (int i = 0; i < board_option; i++)
    {
        printf("%3d ", x);
        x++;
    }
    printf("\n\n");
    
    for (int i = 0; i < board_option; i++)
    {
        printf("%d \t|", y);
        y++;
        for (int j = 0; j < board_option; j++)
        {
            printf(" %c |", visual_board[i][j]);
        }

    printf("\n");
    }
}

void flag(int board_option, char visual_board[15][15])
{
    int x, y = 0;
    do{
        
        printf("Where do you want a flag? x/y\n");
        printf("choose the cordinates of a flag to remove it! x/y\n");
        printf("input: ");
        scanf("%d %d", &x, &y);

        if (x > board_option || x <= 0 || y > board_option || y <= 0)
        {
            printf("invalid option try again.\n");
            x, y = 0;
        }

    } while (x > board_option || y > board_option || x <= 0 || y <= 0);

    --x;
    --y;

    if (visual_board[y][x] == '?')
        visual_board[y][x] = '!';
    else if (visual_board[y][x] == '!')
        visual_board[y][x] = '?';
    else
        printf("flag can't be placed\n");
}

void ask_reveal(int board_option, char visual_board[15][15], int real_board[15][15])
{
    int x, y = 0;
    do{
        
        printf("What space do you want to reveal? x/y\n");
        printf("input: ");
        scanf("%d %d", &x, &y);

        if (x > board_option || x <= 0 || y > board_option || y <= 0)
        {
            printf("invalid option try again.\n");
            x, y = 0;
        }

    } while (x > board_option || y > board_option || x <= 0 || y <= 0);

    --x;
    --y;
    
    if (real_board[y][x] == -1)
    {
        printf("You hit a bomb game over.\n");
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

int reveal(char visual_board[15][15], int real_board[15][15], int x, int y, int board_option)
{
    char number_char[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


    if (visual_board[y][x] != '?')
        return 0;

    visual_board[y][x] = number_char[real_board[y][x]];

    if (real_board[y][x] == 0)
    {    
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i + y >= 0 && j + x >= 0 && i + y < board_option && j + x < board_option)
                {
                    if (visual_board[i + y][j + x] == '?')
                    {
                        int next1 = j+x;
                        int next2 = i+y;
                        reveal(visual_board, real_board, next1, next2, board_option);
                    }
                }
            }
        }
    }
}

int win_check(int board_option, char visual_board[15][15], int real_board[15][15])
{
    int undiscoverd_safe_space = 0;

    for (int i = 0; i < board_option; i++)
        for (int j = 0; j < board_option; j++)
            if ((visual_board[i][j] == '?' || visual_board[i][j] == '!') && real_board[i][j] != -1)
                undiscoverd_safe_space++;

    if (undiscoverd_safe_space == 0)
        return 0;
    else
        return 1;
}