/*************************************************
 *File----------board.c
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 19, 2025 13:33:33 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "board.h"

const float CELL_SIZE = 8;

static void _cellInit(struct Cell *self, int idX, int idY) {
        self->id = (ivec2s){{idX, idY}};

        // Rectangle
        float vertices[] = {
                // Position  // Texture
                1.0f, 1.0f,  0.25f, 0.25f,
                1.0f, 0.0f,  0.25f, 0.0f,
                0.0f, 0.0f,  0.0f, 0.0f,
                0.0f, 1.0f,  0.0f, 0.25f
        };

        unsigned int indices[] = {
                0, 1, 3,
                1, 2, 3
        };

        glGenBuffers(1, &self->vbo);
        glGenBuffers(1, &self->ebo);
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                        vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                        indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                        4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                        4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        float randX = (float)rand() / (float)(RAND_MAX/0.75);
        float randY = (float)rand() / (float)(RAND_MAX/0.75);
        self->texOffset = (vec2s){{randX, randY}};
}

void boardInit(struct Board *self) {
        for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                        _cellInit(&self->cells[y][x], x, y);
                }
        }
        loadTexture(&self->oakTexture, "oak.jpg", GL_RGB, false);
        loadTexture(&self->walnutTexture, "walnut.jpg", GL_RGB, false);
        shaderInit(&self->shader, "board");
}

void boardLoadTransforms(struct Board *self, mat4s view, mat4s projection) {
        shaderUse(&self->shader);
        GLuint viewLoc = glGetUniformLocation(self->shader.handle, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)&view.raw);

        GLuint projLoc = glGetUniformLocation(self->shader.handle, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)&projection.raw);
}

static void _renderCell(struct Cell *self, struct Board *board,
                ivec2s mousePos) {
        glBindVertexArray(self->vao);
        GLuint shaderHandle = board->shader.handle;
        float brightenVal = 1.0f;

        int xOffset = self->id.x - 4;
        int yOffset = self->id.y - 4;
        vec3s translate = {{xOffset * CELL_SIZE, yOffset * CELL_SIZE, 0.0f}};

        mat4s model = mat4_identity();
        model = glms_translate(model, translate);
        model = glms_scale(model, (vec3s){{CELL_SIZE, CELL_SIZE, 1.0f}});

        GLuint modelLoc = glGetUniformLocation(shaderHandle, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)&model.raw);

        GLuint offsetLoc = glGetUniformLocation(shaderHandle, "texOffset");
        glUniform2fv(offsetLoc, 1, (const GLfloat*)self->texOffset.raw);

        glUniform1i(glGetUniformLocation(shaderHandle, "tex"), 0);
        glActiveTexture(GL_TEXTURE0);
        if ((xOffset + yOffset) % 2 == 0) {
                glBindTexture(GL_TEXTURE_2D, board->walnutTexture.handle);
                brightenVal = 1.5f;
        } else {
                glBindTexture(GL_TEXTURE_2D, board->oakTexture.handle);
                brightenVal = 1.3f;
        }

        vec3s color = vec3_one();
        if (mousePos.x == self->id.x && mousePos.y == self->id.y) {
                color = vec3_scale(color, brightenVal);
        }
        GLuint colorLoc = glGetUniformLocation(shaderHandle, "color");
        glUniform3fv(colorLoc, 1, (const GLfloat*)color.raw);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderBoard(struct Board *self, ivec2s mousePos) {
        shaderUse(&self->shader);
        for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                        _renderCell(&self->cells[y][x], self, mousePos);
                }
        }
}

void boardDelete(struct Board *self) {
        for (int i = 0; i < 64; i++) {
        }
        for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                        glDeleteVertexArrays(1, &self->cells[y][x].vao);
                        glDeleteBuffers(1, &self->cells[y][x].vbo);
                        glDeleteBuffers(1, &self->cells[y][x].ebo);
                }
        }
}

