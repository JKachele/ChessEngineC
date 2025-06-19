/*************************************************
 *File----------positions.c
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 19, 2025 16:24:01 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "positions.h"
#include <stdio.h>
#include <string.h>

void fen2Board(struct Positions *self) {
        int row = 0;
        int col = 0;
        int strIndex = 0;
        while (strIndex < (int)strlen(self->fen)) {
                char cur = self->fen[strIndex];

                // If a slash, move down a row
                if (cur == '/') {
                        row++;
                        col = 0;
                        strIndex++;
                        continue;
                }
                // If a number, move that number cols right
                if (cur >= '0' && cur <= '9') {
                        int num = cur - '0';
                        col += num;
                        strIndex++;
                        continue;
                }
                if (row >= 8 || col >= 8) {
                        printf("ERROR: INDEX OUT OF BOUNDS: (%d, %d)\n",
                                        row, col);
                }
                // Switch statement for letters
                switch (cur) {
                case 'p':
                        self->board[row][col] = BLACK|PAWN;
                        break;
                case 'n':
                        self->board[row][col] = BLACK|KNIGHT;
                        break;
                case 'b':
                        self->board[row][col] = BLACK|BISHOP;
                        break;
                case 'r':
                        self->board[row][col] = BLACK|ROOK;
                        break;
                case 'q':
                        self->board[row][col] = BLACK|QUEEN;
                        break;
                case 'k':
                        self->board[row][col] = BLACK|KING;
                        break;
                case 'P':
                        self->board[row][col] = WHITE|PAWN;
                        break;
                case 'N':
                        self->board[row][col] = WHITE|KNIGHT;
                        break;
                case 'B':
                        self->board[row][col] = WHITE|BISHOP;
                        break;
                case 'R':
                        self->board[row][col] = WHITE|ROOK;
                        break;
                case 'Q':
                        self->board[row][col] = WHITE|QUEEN;
                        break;
                case 'K':
                        self->board[row][col] = WHITE|KING;
                        break;
                default:
                        break;
                }
                col++;
                strIndex++;
        }
}

void printBoard(struct Positions *self) {
        const char pieces[16] = "_pnbrqk__PNBRQK_";
        for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                        printf("%c", pieces[self->board[row][col]]);
                }
                printf("\n");
        }
}

void positionsInit(struct Positions *self) {
        char *startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        strncpy(self->fen, startFEN, strlen(startFEN));

        self->toMove = true;
        for (int i = 0; i < 4; i++)
                self->validCastle[i] = true;

        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        self->board[i][j] = 0;
                }
        }
        fen2Board(self);
        // printBoard(self);
}

