/*************************************************
 *File----------window.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 10:59:12 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "window.h"
#include <stdio.h>
#include "../state.h"
#include "GLFW/glfw3.h"

// Global Window
struct Window window;

static void _sizeCallback(GLFWwindow *windowHandle, int width, int height) {
        window.size = (ivec2s){{width, height}};
        glViewport(0, 0, width, height);
        cameraResize(&state.renderer.camera, window.size);
}

static void _mouseCallback(GLFWwindow *windowHandle, double xPos, double yPos) {
        struct Camera *cam = &state.renderer.camera;
        const float sensitivity = 0.1f;
        static float lastX = 400;
        static float lastY = 300;
        static bool firstMouse = true;

        if (firstMouse) {
                lastX = xPos;
                lastY = yPos;
                firstMouse = false;
        }

        float xOffset = (xPos - lastX) * sensitivity;
        float yOffset = (lastY - yPos) * sensitivity;
        lastX = xPos;
        lastY = yPos;
}

static void _keyCallback(GLFWwindow *windowHandle, int key,
                int scancode, int action, int mods) {
        struct Camera *cam = &state.renderer.camera;
        const float cameraSpeed = 2.5f * window.deltaTime;
        if (action == GLFW_PRESS) {
                if (key < (int)(sizeof(window.keysPressed)/
                                sizeof(window.keysPressed[0])) && key >= 0) {
                        window.keysPressed[key] = true;
                        window.keysPressedOnce[key] = true;
                }
        } else if (action == GLFW_RELEASE) {
                if (key < (int)(sizeof(window.keysPressed)/
                                sizeof(window.keysPressed[0])) && key >= 0) {
                        window.keysPressed[key] = false;
                        window.keysPressedOnce[key] = false;
                }
        }
}

void createWindow(WinFunc init, WinFunc render, WinFunc destroy) {
        window.init = init;
        window.render = render;
        window.destroy = destroy;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window.size = (ivec2s){{1000, 1000}};
        window.handle = glfwCreateWindow(window.size.x, window.size.y,
                        "Chess Engine", NULL, NULL);
        if (window.handle == NULL) {
                fprintf(stderr, "Failed to create GLFW window\n");
                glfwTerminate();
                exit(0);
        }
        glfwMakeContextCurrent(window.handle);
        glfwSetFramebufferSizeCallback(window.handle, _sizeCallback);
        glfwSetCursorPosCallback(window.handle, _mouseCallback);
        glfwSetKeyCallback(window.handle, _keyCallback);

        glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                fprintf(stderr, "Failed to initalize GLAD\n");
                exit(0);
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Print FPS to console every 1/2 second
static void _printFPS(void) {
        const float interval = 0.5;
        static float runningTime = 0;
        runningTime += window.deltaTime;

        static int fpsSum = 0;
        static int fpsCount = 0;
        fpsSum += (int)(1 / window.deltaTime);
        fpsCount++;

        if (runningTime > interval) {
                int fps = fpsSum / fpsCount;
                printf("\rFPS: %d", fps);
                fflush(stdout);
                runningTime = 0;
                fpsSum = 0;
                fpsCount = 0;
        }
}

void windowLoop(void) {
        window.init();

        printf("\n");
        while (!glfwWindowShouldClose(window.handle)) {
                glfwPollEvents();
                // processInput(window.handle);

                // Clear Window
                // glClearColor(0.314f, 0.0f, 0.0f, 1.0f);
                glClearColor(0.0f, 0.0f, 0.15f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // Calculate Frame Times
                float currentFrame = glfwGetTime();
                window.deltaTime = currentFrame - window.lastFrame;
                window.lastFrame = currentFrame;
                _printFPS();

                // Rendering happens here
                window.render();

                // Check and call events and swap buffers
                glfwSwapBuffers(window.handle);
                glfwPollEvents();
        }

        window.destroy();

        glfwTerminate();
        exit(0);
}

