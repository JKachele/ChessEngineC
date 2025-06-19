/*************************************************
 *File----------texture.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 14:29:40 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "texture.h"
#include <stdio.h>

static const char *T0_PATH = "assets/textures/container.jpg";
static const char *T1_PATH = "assets/textures/awesomeface.png";

void loadTexture(struct Texture *self, const char *path,
                GLenum format, bool flip) {
        glGenTextures(1, &self->handle);
        glBindTexture(GL_TEXTURE_2D, self->handle);
        
        // Set texture wrapping/filtering options on bound texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load and generate the texture
        stbi_set_flip_vertically_on_load(flip);
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path, &width, &height,
                        &nrChannels, 0);
        if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                                format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
        } else {
                printf("Failed to load texture!\n");
        }
        stbi_image_free(data);
}

