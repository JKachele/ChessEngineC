/*************************************************
 *File----------positions.h
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 19, 2025 16:23:57 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef POSITIONS_H
#define POSITIONS_H

#include "../gfx/gfx.h"

enum PieceType {
        NONE = 0,
        PAWN = 1,
        KNIGHT = 2,
        BISHOP = 3,
        ROOK = 4,
        QUEEN = 5,
        KING = 6
};

enum Color {
        BLACK = 0,
        WHITE = 8
};

struct Positions {
        char fen[100];
        bool toMove; // White if true
        bool validCastle[4]; // KQkq
        ivec2s enPassant;
        int halfmoves;
        int fullmoves;

        int board[8][8];
};

void positionsInit(struct Positions *self);

#endif

