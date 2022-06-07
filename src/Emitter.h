#pragma once

#include "ofMain.h"
#include "Shape.h"
#include "Sprite.h"


//
//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteList {
public:
    void add(Sprite);
    void remove(int);
    void update();
    void draw();
    vector<Sprite> sprites;
};



//
class Emitter : public Shape {
public:
    Emitter();
    void init();
    void draw();
    void start();
    void stop();
    void setLifespan(float);
    void setVelocity(const glm::vec3 v);
    void setChildImage(ofImage);
    void setImage(ofImage);
    void setRate(float);
    void update(glm::vec3, vector<glm::vec3>, glm::mat4 T);

    // virtuals - can overloaded
    virtual void moveSprite(Sprite *, glm::vec3, vector<glm::vec3>, glm::mat4 T);
    virtual void spawnSprite(glm::vec3);

    SpriteList *sys;
    float rate;
    glm::vec3 velocity;
    float lifespan;
    bool started;
    float lastSpawned;
    ofImage childImage;
    ofImage image;
    bool drawable;
    bool haveChildImage;
    bool haveImage;
    float width, height;
    int energy;
};

