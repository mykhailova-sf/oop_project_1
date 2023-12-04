#include <time.h>
#include "Player.h"
#include <SFML/Window.hpp>
#include <GL/glu.h>
#include <cmath>
#include <iostream>

#define BULKA 3
#define EMPTY 0
#define CUBE 1
#define GLASSES 6
#define BOOT 7
#define SNICKERS 5

GLuint box[6];

extern GLint GLASSES_TEXTURE;
extern GLint BOOT_TEXTURE;
extern GLint GRASS_TEXTURE;
extern GLint BOTTOM_TEXTURE;
extern GLint SIDE_TEXTURE;
extern GLint BULKA_TEXTURE;
extern GLint EMPTY_BULKA_TEXTURE;
extern GLint GAME_OVER_TEXTURE;
extern GLint SNICKERS_TEXTURE;
extern GLint WINNER_TEXTURE;

class Cube {
private:
    float h = 7.0f;
    float size;
public:
    Cube(float size) : size(size) {}

    void draw() const {
        float halfSize = size / 2.0f;

        glEnable(GL_TEXTURE_2D);

        // Bottom face
        glBindTexture(GL_TEXTURE_2D, box[4]);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSize, 0, halfSize);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(halfSize, 0, halfSize);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(halfSize, 0, -halfSize);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfSize, 0, -halfSize);
        glEnd();

        // Top face
        glBindTexture(GL_TEXTURE_2D, box[5]);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSize, h, halfSize);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(halfSize, h, halfSize);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(halfSize, h, -halfSize);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfSize, h, -halfSize);
        glEnd();
        // Front face
        glBindTexture(GL_TEXTURE_2D, box[0]);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSize, 0, halfSize);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(halfSize, 0, halfSize);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(halfSize, h, halfSize);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfSize, h, halfSize);
        glEnd();

        // Left face
        glBindTexture(GL_TEXTURE_2D, box[0]);
        glNormal3f(-0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSize, 0, halfSize);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfSize, 0, -halfSize);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfSize, h, -halfSize);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfSize, h, halfSize);
        glEnd();

        // Back face
        glBindTexture(GL_TEXTURE_2D, box[0]);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfSize, 0, -halfSize);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(halfSize, 0, -halfSize);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(halfSize, h, -halfSize);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfSize, h, -halfSize);
        glEnd();

        // Right face
        glBindTexture(GL_TEXTURE_2D, box[0]);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(halfSize, 0, halfSize);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(halfSize, 0, -halfSize);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(halfSize, h, -halfSize);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(halfSize, h, halfSize);
        glEnd();

        glDisable(GL_TEXTURE_2D);
  }

};

void drawOnGround(int i, int j, GLuint texture);
void drawHorizontalSquare(int i, int j, GLuint texture, float height);
void drawStuff();
void drawAbdomen();
void drawArtifact(int i, float shift, int row, float size, GLuint texture);

void drawTimer(long time);

long getCurrentTime();

void checkGameTime();

void restart();

void resetPosition();

void cloneWorld();

void addPrizeTime();

long computeLeftTime();

void drawEndGameBanner(GLint);

const int worldSize = 15;
static const long PRIZE_TIME = 15;
int world[worldSize][worldSize];

int originWorld[worldSize][worldSize] = {
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, BULKA, 1, 1, 0, 0, 0, 0, 0, 0, 0, BULKA, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SNICKERS},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, BULKA, 0, 1, 0, 0, 0, 0, 0, 0, 0, BULKA, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
};

float centerX;
float centerZ;
float eyeX;
float eyeY;
float eyeZ;

float wSize = 10.0f * worldSize;
int gameTime = 50;
long startAt;
long leftTime;

sf::Window window(sf::VideoMode(800 + 200, 600 + 200), "SPH");

Player player;

void init() {
    cloneWorld();
    box[3] = box[2] = box[1] = box[0] = SIDE_TEXTURE;
    box[4] = BOTTOM_TEXTURE;
    box[5] = GRASS_TEXTURE;

    startAt = getCurrentTime();
    leftTime = gameTime;

    resetPosition();
    std::cout << "Absolute time in seconds: " << startAt << std::endl;
}

void cloneWorld() {
    for (int i = 0; i < worldSize; i ++) {
        for (int j = 0; j < worldSize; j ++) {
            world[i][j] = originWorld[i][j];
        }
    }
}

void resetPosition() {
    centerX = 50.0f;
    centerZ = 0.0f;
    eyeX = 5.0f;
    eyeY = 5.0f;
    eyeZ = 95.0f;
}

long getCurrentTime() {
    return time(0);
}

bool isInsideWorld(float x, float y) {
    return (x > 0.00 && x < wSize) 
        && (y > 0.00 && y < wSize);
}

bool isOccupied(float x, float z) {
    int kx =(int) (x / 10);
    int kz = (int) (z / 10);

    return world[kx][kz] == CUBE;
}

void drawWorld() {
    glNormal3f(0.0f, 0.0f, 1.0f);

    for (int i = 0; i < worldSize; ++i) {
        for (int j = 0; j < worldSize; ++j) {
            if (world[i][j] != CUBE) {
                drawOnGround(i, j, GRASS_TEXTURE);
            }
            if (world[i][j] == BULKA) {
                drawOnGround(i, j, BULKA_TEXTURE);
            }
            if (world[i][j] == GLASSES) {
                drawOnGround(i, j, GLASSES_TEXTURE);
            }
            if (world[i][j] == BOOT) {
                drawOnGround(i, j, BOOT_TEXTURE);
            }
            if (world[i][j] == SNICKERS) {
                drawOnGround(i, j, SNICKERS_TEXTURE);
            }
        }
    }

    for (int i = 0; i < worldSize; ++i) {
        for (int j = 0; j < worldSize; ++j) {
            if (world[i][j] == CUBE) {
                glPushMatrix();
                glTranslatef(i * 10.0f + 5.0f,
                             0.0f,
                             j * 10.0f + 5.0f);  // Положення кубиків на підлозі
                Cube cube(10.0f);
                cube.draw();
                glPopMatrix();
            }
        }
    }
}

void drawOnGround(int i, int j, GLuint texture) {
    drawHorizontalSquare(i, j, texture, 0);
}

void drawHorizontalSquare(int i, int j, GLuint texture, float height) {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f); // Білий колір, щоб текстура відобразилась правильно
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(i * 10.0f, height, j * 10.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(i * 10.0f + 10.01f, height, j * 10.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(i * 10.0f + 10.01f, height, j * 10.0f + 10.01f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(i * 10.0f, height, j * 10.0f + 10.01f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void showDebugData() {
//    std::cout << "Camera Position: (" << eyeX << ", " << eyeY << ", " << eyeZ << "), Camera Rotation: " <<  " degrees\n";
//    std::cout << "   Obj Position: (" << centerX << ", " << eyeY << ", " << centerZ << "), Camera Rotation: " <<  " degrees\n";
}

void update() {
    leftTime = computeLeftTime();

    if (
            player.isBootsActivated()
            && getCurrentTime() - player.getTimeBootsActivated() > Player::MAX_TIME_WITH_BOOTS
       ) {
        player.takeOffBoot();
    }

    // Відновлення координат камери
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        // Рух вперед

        float dirX = -(eyeX - centerX);
        float dirZ = -(eyeZ - centerZ);

        // Нормалізуемо вектор направлення
        float length = std::sqrt(dirX * dirX + dirZ * dirZ);
        float dirXNormalized = dirX / length;
        float dirZNormalized = dirZ / length;

        // Переміщуємо камеру вперед
        float newEyeX = eyeX + player.getSpeed() * dirXNormalized;
        float newEyeZ =  eyeZ + player.getSpeed() * dirZNormalized;
        if (isInsideWorld(newEyeX, newEyeZ) && !isOccupied(newEyeX, newEyeZ)) {
            eyeZ = newEyeZ;
            eyeX = newEyeX;
            centerX += player.getSpeed() * dirXNormalized;
            centerZ += player.getSpeed() * dirZNormalized;
        }
        showDebugData();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        float dirX = -(eyeX - centerX);
        float dirZ = -(eyeZ - centerZ);

        // Поворот на 90 градусів
        float rotatedX = -dirZ;
        float rotatedZ = dirX;
        // Нормалізуємо вектор направлення
        float length = std::sqrt(rotatedX * rotatedX + rotatedZ * rotatedZ);
        float dirXNormalized = rotatedX / length;
        float dirZNormalized = rotatedZ / length;

        // Перемещаем камеру вперед
        float newEyeX = eyeX - player.getSpeed() * dirXNormalized;
        float newEyeZ =  eyeZ - player.getSpeed() * dirZNormalized;
        if (isInsideWorld(newEyeX, newEyeZ) && !isOccupied(newEyeX, newEyeZ)) {
            eyeZ = newEyeZ;
            eyeX = newEyeX;
            centerX -= player.getSpeed() * dirXNormalized;
            centerZ -= player.getSpeed() * dirZNormalized;
        }
        showDebugData();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        // Поворот вліво
        float rad = -0.1f * M_PI / 180;
        float x = centerX - eyeX;
        float z = centerZ - eyeZ;
        float x_new = x * cos(rad) - z * sin(rad);
        float z_new = x * sin(rad) + z * cos(rad);
        centerX = x_new + eyeX;
        centerZ = z_new + eyeZ;
        showDebugData();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        // Поворот вправо
        float rad = 0.1f * M_PI / 180;
        float x = centerX - eyeX;
        float z = centerZ - eyeZ;
        float x_new = x * cos(rad) - z * sin(rad);
        float z_new = x * sin(rad) + z * cos(rad);
        centerX = x_new + eyeX;
        centerZ = z_new + eyeZ;
        showDebugData();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        // Рух назад
        float dirX = -(eyeX - centerX);
        float dirZ = -(eyeZ - centerZ);

        // Нормалізуємо вектор направлення
        float length = std::sqrt(dirX * dirX + dirZ * dirZ);
        float dirXNormalized = dirX / length;
        float dirZNormalized = dirZ / length;

        // Переміщуємо камеру вперед
        float newEyeX = eyeX - player.getSpeed() * dirXNormalized;
        float newEyeZ =  eyeZ - player.getSpeed() * dirZNormalized;
        if (isInsideWorld(newEyeX, newEyeZ) && !isOccupied(newEyeX, newEyeZ)) {
            eyeZ = newEyeZ;
            eyeX = newEyeX;
            centerX -= player.getSpeed() * dirXNormalized;
            centerZ -= player.getSpeed() * dirZNormalized;
        }
        showDebugData();

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // Поворот вправо
        float dirX = -(eyeX - centerX);
        float dirZ = -(eyeZ - centerZ);

        // Поворот на 90 градусів
        float rotatedX = -dirZ;
        float rotatedZ = dirX;
        float length = std::sqrt(rotatedX * rotatedX + rotatedZ * rotatedZ);
        float dirXNormalized = rotatedX / length;
        float dirZNormalized = rotatedZ / length;

        // Переміщуємо камеру вперед

        float newEyeX = eyeX + player.getSpeed() * dirXNormalized;
        float newEyeZ =  eyeZ + player.getSpeed() * dirZNormalized;
        if (isInsideWorld(newEyeX, newEyeZ) && !isOccupied(newEyeX, newEyeZ)) {
            eyeZ = newEyeZ;
            eyeX = newEyeX;
            centerX += player.getSpeed() * dirXNormalized;
            centerZ += player.getSpeed() * dirZNormalized;
        }
        showDebugData();
    }


    int x =(int) (eyeX / 10);
    int z = (int) (eyeZ / 10);

    if (world[x][z] == BULKA && leftTime != 0) {
        if (player.eatBun()) {
            world[x][z] = EMPTY;

        }
    }

    if (world[x][z] == SNICKERS && leftTime != 0) {
        addPrizeTime();
        world[x][z] = EMPTY;
    }
}

void addPrizeTime() {
    long elapsed = gameTime - leftTime;
    long i = (elapsed < PRIZE_TIME) ? elapsed : PRIZE_TIME;
    startAt += i;
}

void processKeyPressed(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::R) {
        restart();
    }

    int x =(int) (eyeX / 10);
    int z = (int) (eyeZ / 10);

    if (key == sf::Keyboard::Num1 &&  world[x][z] != GLASSES) {
        if (player.throwAwayGlasses()) {
            world[x][z] = GLASSES;
        }
    }

    if (key== sf::Keyboard::Num2 &&  world[x][z] != BOOT) {
        if (player.throwAwayBoot()) {
            world[x][z] = BOOT;
        }
    }

    if (key== sf::Keyboard::Num3) {
        player.takeOnBoot();
    }

    if (key== sf::Keyboard::LShift) {
        if (eyeY < 4.0f) {
            eyeY = 5.0f;
        } else {
            eyeY = 3.0f;
        }
    }
}

void restart() {
    cloneWorld();
    leftTime = gameTime;
    startAt = getCurrentTime();
    player = Player();
    resetPosition();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 3D-проекція
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, window.getSize().x / window.getSize().y, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    // Позиціонуємо камеру
    gluLookAt(eyeX, eyeY, eyeZ, centerX, eyeY, centerZ,0, 1, 0);

    drawWorld();  // Малюємо кімнату

    // Встановлюємо матрицю проекції ортографічной камери
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window.getSize().x, window.getSize().y, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawStuff();
    drawAbdomen();

    drawTimer(leftTime);

    // CHECK WINNER
    if (player.getNumberOfBunsInStomack() == Player::STOMACH_CAPACITY) {
        glColor3f(1.0f, 1.0f, 1.0f);
        drawEndGameBanner(WINNER_TEXTURE);
    } else {
        checkGameTime();
    }

    window.display();
}

void checkGameTime() {
    if (leftTime == 0) {
        drawEndGameBanner(GAME_OVER_TEXTURE);
    }
}

void drawEndGameBanner(GLint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(250, 150);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(550, 150);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(550, 450);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(250, 450);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void drawTimer(long time) {
    int wholeBarW = 200;
    long leftPercent = time * 100 / gameTime;
    int leftW =  int (leftPercent * wholeBarW / 100);
    glColor3f(77, 72, 72);
    glBegin(GL_QUADS);
        glVertex2f(20.0f, 3.0f);
        glVertex2f(20.0f + wholeBarW, 3.0f);
        glVertex2f(20.0f + wholeBarW, 20.0f);
        glVertex2f(20.0f, 20.0f);
    glEnd();
    if (leftPercent < 50) {
        glColor3f(255, 0, 0);
    } else {
        glColor3f(0, 255, 0);
    }
    glBegin(GL_QUADS);
        glVertex2f(20.0f, 3.0f);
        glVertex2f(20.0f + leftW, 3.0f);
        glVertex2f(20.0f + leftW, 20.0f);
        glVertex2f(20.0f, 20.0f);
    glEnd();

}

long computeLeftTime() {
    long time = gameTime - (getCurrentTime() - startAt);

    return (time < 0) ? time = 0 : time;
}

void drawStuff() {
    int stuffCount = player.getCurrentNumberOfItemsInPocket();
    if (stuffCount == 0) {
        return;
    }
    
    for (int i = 0; i < stuffCount; i++) {
        drawArtifact(i % 3, 450 + 200, i / 3, 100, player.getArtifact(i).getTexture());
    }
}

void drawAbdomen() {
    for (int i = 0; i < player.STOMACH_CAPACITY; i++) {
        drawArtifact(
                i,
                0,
                0,
                100,
                (i < player.getNumberOfBunsInStomack()) ? BULKA_TEXTURE : EMPTY_BULKA_TEXTURE
        );
    }
}

void drawArtifact(int i, float shift, int row, float size, GLuint texture) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(i*size + shift + 10.0f, row*size + 10.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(i*size + shift + size, row*size + 10.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(i*size + shift + size, row*size + size);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(i*size + shift + 10.0f, row*size + 100.0f);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0); // Відвʼязуємо текстуру
        glDisable(GL_TEXTURE_2D);
}

void processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();

        } else if (event.type == sf::Event::KeyPressed) {
            processKeyPressed(event.key.code);
        }
    }
}

int main() {
    player = Player();
    std::cout << "Name: " << player.getName() << std::endl;

    init();

    while (window.isOpen()) {
        processEvents();
        update();
        display();
    }

    return 0;
}
