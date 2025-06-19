/*************************************************
 *File----------state.h
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 13:04:39 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef STATE_H
#define STATE_H

#include "gfx/gfx.h"
#include "gfx/render.h"
#include "game/positions.h"

struct state{
        struct Window *window;
        struct Renderer renderer;
        struct Positions positions;
};

// Global State
extern struct state state;

#endif

