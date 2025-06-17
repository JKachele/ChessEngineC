/*************************************************
 *File----------window.h
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 10:59:31 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef WINDOW_H
#define WINDOW_H

#include "gfx.h"

typedef void (*WinFunc)(void);

struct Window {
        GLFWwindow *handle;
        ivec2s size;

        // Timing variables
        float deltaTime;
        float lastFrame;

        // Keys
        bool keysPressed[350];
        bool keysPressedOnce[350];

        WinFunc init;
        WinFunc render;
        WinFunc destroy;
};

// Global Window
extern struct Window window;

void createWindow(WinFunc init, WinFunc render, WinFunc destroy);
void windowLoop(void);

#endif

