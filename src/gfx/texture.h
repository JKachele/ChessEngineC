/*************************************************
 *File----------texture.h
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 14:29:49 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef TEXTURE_H
#define TEXTURE_H

#include "gfx.h"

struct Texture{
        GLuint handle;
        GLuint handle0;
        GLuint handle1;
};

void loadTexture(struct Texture *self, const char *name,
                GLenum format, bool flip);

#endif

