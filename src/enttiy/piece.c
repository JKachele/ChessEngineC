/*************************************************
 *File----------piece.c
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 19, 2025 12:41:33 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "piece.h"

void pieceInit(struct Piece *self) {
        // Rectangle
        float vertices[] = {
                // Position  // Texture
                1.0f, 1.0f,  0.167f, 0.5f,
                1.0f, 0.0f,  0.167f, 0.0f,
                0.0f, 0.0f,  0.0f,   0.0f,
                0.0f, 1.0f,  0.0f,   0.5f
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

        shaderInit(&self->shader, "piece");
        loadTexture(&self->pieceAtlas, "pieces.png", GL_RGBA, true);
}

void pieceLoadTransforms(struct Piece *self, mat4s view, mat4s projection) {
        shaderUse(&self->shader);
        GLuint viewLoc = glGetUniformLocation(self->shader.handle, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)&view.raw);

        GLuint projLoc = glGetUniformLocation(self->shader.handle, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)&projection.raw);
}

static vec3s getPieceOffset(int id) {
        int typeID = (id & 7) - 1; // 0111
        int colorID = id >> 3;

        float xOffset = 0.167f * typeID;
        float yOffset = 0.5f * colorID;

        return (vec3s){{xOffset, yOffset, 0.0}};
}

static void renderPiece(struct Piece *self, int id, int row, int col) {
        shaderUse(&self->shader);
        glBindVertexArray(self->vao);

        // Flip row from top-bottom to bottom-top;
        row = (7 - row) - 4;
        col = col - 4;
        vec3s translate = {{(col * 8) + 0.5f, (row * 8), 0.0f}};

        mat4s model = mat4_identity();
        model = glms_translate(model, translate);
        model = glms_scale(model, (vec3s){{7.0f, 7.0f, 1.0f}});

        GLuint modelLoc = glGetUniformLocation(self->shader.handle, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)&model.raw);

        vec3s offset = getPieceOffset(id);
        GLuint offsetLoc = glGetUniformLocation(self->shader.handle, "texOffset");
        glUniform2fv(offsetLoc, 1, (const GLfloat*)offset.raw);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, self->pieceAtlas.handle);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderPieces(struct Piece *self, struct Positions *positions) {
        for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                        int piece = positions->board[row][col];
                        if (piece != 0)
                                renderPiece(self, piece, row, col);
                }
        }
}

void pieceDelete(struct Piece *self) {
        glDeleteVertexArrays(1, &self->vao);
        glDeleteBuffers(1, &self->vbo);
        glDeleteBuffers(1, &self->ebo);
}


