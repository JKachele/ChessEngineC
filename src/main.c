/*************************************************
 *File----------main.c
 *Project-------ChessEngine
 *Author--------Justin Kachele
 *Created-------Thursday Jan 16, 2025 09:18:51 EST
 *License-------GNU GPL-3.0
 ************************************************/

#include "gfx/render.h"
#include "state.h"
#include "gfx/window.h"

// Global State
struct state state;

void init(void) {
        state.window = &window;
        renderInit(&state.renderer);
        positionsInit(&state.positions);
}

void update(void) {
        renderUpdate(&state.renderer, state.window->size);
}

void render(void) {
        renderEntities(&state.renderer, &state.positions);
}

void destroy(void) {
        renderDestroy(&state.renderer);
        printf("\nGoodbye!\n");
}

int main(void) {
        createWindow(init, update, render, destroy);
        windowLoop();
}

