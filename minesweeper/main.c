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
        {
            printf("\"%s\" is not a valid option try again.\n", answer);
        }
    }

    int real_board[15][15] = {0};
    int visual_board[15][15] = {0};
    int bombs = 0;

    make_board(board_option, real_board, bombs);

    print_board(board_option, visual_board);

    while (1)
    {
        ask_reveal(board_option, visual_board, real_board);

        print_board(board_option, visual_board);
    }

    return 0;
}


int make_board(int board_option, int real_board[15][15], int bombs)
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
                ++bombs;
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

int print_board(int board_option, int visual_board[15][15])
{
    for (int i = 0; i < board_option; i++)
    {
        for (int j = 0; j < board_option; j++)
        {
            printf("%d ", visual_board[i][j]);
        }
    printf("\n");
    }
}


int ask_reveal(int board_option, int visual_board[15][15], int real_board[15][15])
{
    int answer[2] = {0};
    do{
        printf("whate space do you want te reveal? y x\n");
        printf("input: ");
        scanf("%d %d", &answer[0], &answer[1]);
        for (int i = 0; i < 2; i++)
        {
            if (answer[i] > board_option || answer[i] <= 0)
            {
                printf("invalid option try again.");
            }
        }
    } while (answer[0] > board_option || answer[1] > board_option || answer[0] <= 0 || answer[1] <= 0);

    for (int i = 0; i < 2; i++)
        --answer[i];
    
    
    if (real_board[answer[0]][answer[1]] == -1)
    {
        printf("You hit a bomb game over.\n");
        printf("press any key to exit.\n");
        getchar();
        getchar();
        exit(1);
    }
    else
    {
        reveal(visual_board, real_board, answer, board_option);
    }
}


int reveal(int visual_board[15][15], int real_board[15][15], int answer[2], int board_option)
{
    visual_board[answer[0]][answer[1]] = real_board[answer[0]][answer[1]];

    if (real_board[answer[0]][answer[1]] == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                visual_board[i + answer[0]-1][j + answer[1]-1] = real_board[i + answer[0]-1][j + answer[1]-1];
            }
        }
    }    
}