#ifndef SPH_TEXTURELOADER_H
#define SPH_TEXTURELOADER_H

#include <GL/glu.h>
#include <iostream>
#include <SOIL/SOIL.h>

inline GLuint LoadTexture(const char *name) {
    GLuint texture = SOIL_load_OGL_texture(
            name,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    if (!texture) {
        std::cerr << "Error loading texture: " << SOIL_last_result() << std::endl;
    } else {
        std::cerr << "Texture: "  << name << " - "<< SOIL_last_result() << std::endl;
    }
    return texture;
}

#endif // SPH_TEXTURELOADER_H
