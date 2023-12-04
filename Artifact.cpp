#include "Artifact.h"

extern GLint GLASSES_TEXTURE;
extern GLint BOOT_TEXTURE;
extern GLint TAKED_BOOT_TEXTURE;

GLuint Artifact::getTexture() const {
    return (takedOn)? takedTexture : texture;
}

ArtifactType Artifact::getType() {
    return type;
}

void Artifact::markAsTakedOn() {
    takedOn = true;
}

void Artifact::markAsTakedOff() {
    takedOn = false;
}

bool Artifact::getTakedStatus() {
    return takedOn;
}

Glasses::Glasses() {
    texture = GLASSES_TEXTURE;
    takedTexture = GLASSES_TEXTURE;
    type = GLASSES;
}

Boot::Boot() {
    texture = BOOT_TEXTURE;
    takedTexture = TAKED_BOOT_TEXTURE;
    type = BOOT;
}

