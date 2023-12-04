
#ifndef SPH_ARTIFACT_H
#define SPH_ARTIFACT_H

#include <GL/glut.h>

enum ArtifactType {
    BOOT,
    GLASSES,
    SOMETHING
};

class Artifact {
    public:
        virtual GLuint getTexture() const;
        virtual void markAsTakedOn();
        virtual void markAsTakedOff();
        virtual bool getTakedStatus();
        virtual ~Artifact() = default;

        virtual ArtifactType getType();

    protected:
        GLint texture;
        GLint takedTexture;
        bool takedOn = false;
        ArtifactType type;
};

class Glasses : public Artifact {
    public:
        Glasses();
};

class Boot : public Artifact {
    public:
        Boot();
};


#endif //SPH_ARTIFACT_H
