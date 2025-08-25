#ifndef HEADER_H
#define HEADER_H

int make_board(int board_option, int real_board[15][15], int bombs);
int print_board(int board_option, int visual_board[15][15]);
int ask_reveal(int board_option, int visual_board[15][15], int real_board[15][15]);
int reveal(int visual_board[15][15], int real_board[15][15], int answer[2], int board_option);

enum {SMALL = 5, MEDIUM = 8, LARGE = 15};
enum {SAFE, BOMB = -1};

#endif