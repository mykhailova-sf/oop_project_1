#ifndef SPH_PLAYER_H
#define SPH_PLAYER_H

#include <string>
#include <time.h>
#include "Artifact.h"

class Player {
    public:
        Player();  // Конструктор
        ~Player(); // Деструктор

        Artifact getArtifact(int i);

        static const int STOMACH_CAPACITY = 4;
        static const int MAX_TIME_WITH_BOOTS = 10;
        std::string getName() const;
        int getCurrentNumberOfItemsInPocket() const;
        int getNumberOfBunsInStomack() const;
        float getSpeed() const;
        bool throwAwayBoot();
        bool isBootsActivated();
        bool throwAwayGlasses();
        bool eatBun();
        void takeOnBoot();
        void takeOffBoot();

    private:
        static const int POCKET_CAPACITY = 4;

        std::string name;
        int bunsCount;
        long timeBootsActivated;
public:
    long getTimeBootsActivated() const;

private:
        int bootsOnFoots = 0;
        float speed;
        float extraSpeed;
        int artifactsCount;
        Artifact artifacts[POCKET_CAPACITY];
        bool throwAwaySmth(ArtifactType);
        void updateExtraSpeed();
};


#endif //SPH_PLAYER_H
