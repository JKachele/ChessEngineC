/*************************************************
 *File----------cell.c
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Wednesday Jun 18, 2025 17:08:02 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "cell.h"

void cellInit(struct Cell *self, int id) {
        self->id = id;
        self->pieceID = 0;

        // Rectangle
        float vertices[] = {
                // Position 
                1.0f,  1.0f,
                1.0f,  0.0f,
                0.0f,  0.0f,
                0.0f,  1.0f
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
                        2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
}

void renderCell(struct Cell *self, GLuint shaderHandle) {
        glBindVertexArray(self->vao);

        int xOffset = self->id % 8;
        int yOffset = self->id / 8;
        vec3s translate = {{xOffset, yOffset, 0.0f}};

        mat4s model = mat4_identity();
        model = glms_scale(model, (vec3s){{8.0f, 8.0f, 8.0f}});
        model = glms_translate(model, translate);

        GLuint modelLoc = glGetUniformLocation(shaderHandle, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)&model.raw);

        GLuint colorLoc = glGetUniformLocation(shaderHandle, "color");
        if ((xOffset + yOffset) % 2 == 0) {
                glUniform3f(colorLoc, 0.4667f, 0.2471f, 0.1020f);
        } else {
                glUniform3f(colorLoc, 0.85f, 0.71f, 0.54f);
        }

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void cellDelete(struct Cell *self) {
        glDeleteVertexArrays(1, &self->vao);
        glDeleteBuffers(1, &self->vbo);
        glDeleteBuffers(1, &self->ebo);
}

