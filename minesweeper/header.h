#ifndef HEADER_H
#define HEADER_H

void make_board(int board_option, int real_board[15][15]);
void print_board(int board_option, char visual_board[15][15]);
void flag(int board_option, char visual_board[15][15]);
void ask_reveal(int board_option, char visual_board[15][15], int real_board[15][15]);
int reveal(char visual_board[15][15], int real_board[15][15], int x, int y, int board_option);
int win_check(int board_option, char visual_board[15][15], int real_board[15][15]);

#define BOMB  -1

enum {SMALL = 5, MEDIUM = 8, LARGE = 15};

#endif