#include "Player.h"
#include "Artifact.h"

Player::Player() {
    name = "Sph";
    bunsCount = 0;
    artifacts[0] = Glasses();
    artifacts[1] = Boot();
    artifacts[2] = Boot();
    artifactsCount = 3;
    speed = 0.025f;
    extraSpeed = 0;
    bootsOnFoots = 0;
    timeBootsActivated = 0;
}

Player::~Player() {}

std::string Player::getName() const {
    return name;
}

bool Player::eatBun() {
    if (bunsCount == STOMACH_CAPACITY) {
        return false;
    }
    bunsCount++;

    return true;
}

int Player::getCurrentNumberOfItemsInPocket() const {
    return artifactsCount;
}

Artifact Player::getArtifact(int i) {
    if (i < 0 || i >= POCKET_CAPACITY) {
        // TODO
    }

    return artifacts[i];
}

int Player::getNumberOfBunsInStomack() const {
    return bunsCount;
}

bool Player::throwAwayBoot() {
    return throwAwaySmth(ArtifactType::BOOT);
}

bool Player::throwAwayGlasses() {
    return throwAwaySmth(ArtifactType::GLASSES);
}

bool Player::throwAwaySmth(ArtifactType type) {
    if (artifactsCount == 0) {
        false;
    }

    for (int indexToRemove = 0; indexToRemove < artifactsCount; indexToRemove++) {
        if (type == artifacts[indexToRemove].getType()) {
            // Зсуваємо елементи що залишилися
            for (int i = indexToRemove; i < artifactsCount - 1; ++i) {
                artifacts[i] = artifacts[i + 1];
            }
            --artifactsCount;

            return true;
        }
    }

    return false;
}

float Player::getSpeed() const {
    return speed + extraSpeed;
}

void Player::takeOnBoot() {
    for (int i = 0; i < artifactsCount; i++) {
        if (ArtifactType::BOOT == artifacts[i].getType() && !artifacts[i].getTakedStatus()) {
            artifacts[i].markAsTakedOn();
            if (bootsOnFoots < 2) {
                bootsOnFoots++;
                if (bootsOnFoots == 2) {
                    timeBootsActivated = time(0);
                }
                updateExtraSpeed();

                return;
            }
        }
    }
}

void Player::updateExtraSpeed() {
    if (bootsOnFoots == 1) {
        extraSpeed = -0.015f;
    }
    if (bootsOnFoots == 2) {
        extraSpeed = 0.025f;
    }
    if (bootsOnFoots == 0) {
        extraSpeed = 0.0f;
    }
}

void Player::takeOffBoot() {
    for (int i = 0; i < artifactsCount; i++) {
        if (ArtifactType::BOOT == artifacts[i].getType() && artifacts[i].getTakedStatus()) {
            artifacts[i].markAsTakedOff();
            if (bootsOnFoots > 0) {
                --bootsOnFoots;
                timeBootsActivated = 0;
                updateExtraSpeed();
            }
        }
    }

}

long Player::getTimeBootsActivated() const {
    return timeBootsActivated;
}

bool Player::isBootsActivated() {
    return timeBootsActivated != 0;
}
