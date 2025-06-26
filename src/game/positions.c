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
        char *fen = self->fen;
        int strIndex = 0;

        // Get piece positions
        int row = 0;
        int col = 0;
        while (strIndex < (int)strlen(fen) && fen[strIndex] != ' ') {
                char cur = fen[strIndex];

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
        strIndex++;
        if (strIndex >= (int)strlen(fen)) return;

        // Get side to move
        if (fen[strIndex] == 'w')
                self->toMove = true;
        else
                self->toMove = false;
        strIndex += 2;
        if (strIndex >= (int)strlen(fen)) return;

        // Get Castling ability
        while (strIndex < (int)strlen(fen) && fen[strIndex] != ' ') {
                switch (fen[strIndex]) {
                case 'K':
                        self->validCastle[0] = true;
                        break;
                case 'Q':
                        self->validCastle[1] = true;
                        break;
                case 'k':
                        self->validCastle[2] = true;
                        break;
                case 'q':
                        self->validCastle[3] = true;
                        break;
                default:
                        break;
                }
                strIndex++;
        }
        strIndex++;
        if (strIndex >= (int)strlen(fen)) return;

        // Get En passant
        if (fen[strIndex] != '-') {
                int row = fen[strIndex] - 'a';
                strIndex++;
                if (strIndex >= (int)strlen(fen)) return;
                int col = fen[strIndex] - '0';
                self->enPassant = (ivec2s){{row, col}};
        }
        strIndex++;
        if (strIndex >= (int)strlen(fen)) return;

        // Get Halfmoves
        while (strIndex < (int)strlen(fen) && fen[strIndex] != ' ') {
                int num = fen[strIndex] - '0';
                self->halfmoves = (self->halfmoves * 10) + num;
                strIndex++;
        }
        strIndex++;
        if (strIndex >= (int)strlen(fen)) return;

        // Get Fullmoves
        while (strIndex < (int)strlen(fen) && fen[strIndex] != ' ') {
                int num = fen[strIndex] - '0';
                self->fullmoves = (self->fullmoves * 10) + num;
                strIndex++;
        }
}

void printBoard(struct Positions *self) {
        const char pieces[16] = "_pnbrqk__PNBRQK_";
        printf("\n");
        for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                        printf("%c", pieces[self->board[row][col]]);
                }
                printf("\n");
        }
        printf("\n");
        printf("%s to move\n", self->toMove ? "White" : "Black");
        printf("Valid Castles: ");
        if (self->validCastle[0])
                printf("K");
        if (self->validCastle[1])
                printf("Q");
        if (self->validCastle[2])
                printf("k");
        if (self->validCastle[3])
                printf("q");
        printf("\n");

        if (self->enPassant.x == -1)
                printf("En passant: -\n");
        else
                printf("En passant: %c%d\n", (char)self->enPassant.x + 'a',
                                self->enPassant.y);

        printf("Halfmoves: %d\n", self->halfmoves);
        printf("Fullmoves: %d\n", self->fullmoves);
}

void positionsInit(struct Positions *self) {
        char *startFEN =
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        char *exFEN = 
                "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
        // strncpy(self->fen, startFEN, strlen(startFEN));
        strncpy(self->fen, exFEN, strlen(exFEN));

        self->toMove = true;
        for (int i = 0; i < 4; i++)
                self->validCastle[i] = false;

        self->enPassant = (ivec2s){{-1, -1}};
        self->halfmoves = 0;
        self->fullmoves = 0;

        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        self->board[i][j] = 0;
                }
        }
        fen2Board(self);
        printBoard(self);
}

