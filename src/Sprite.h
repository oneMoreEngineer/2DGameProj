#pragma once

#include "Shape.h"



class TriangleShape : public Shape {
public:
    TriangleShape() {
        // default data
        set(glm::vec3(20, 20, 0), glm::vec3(0, -40, 0), glm::vec3(-20, 20, 0));
    }
    virtual void draw();
    //virtual bool inside(const glm::vec3 p);
    virtual bool inside(vector<glm::vec3> p, glm::vec3 a, glm::mat4 T);

    void set(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
        verts.clear();
        verts.push_back(v1);
        verts.push_back(v2);
        verts.push_back(v3);
    }
};

class Sprite : public TriangleShape {
public:

    void draw() {
        if (bShowImage) {
            ofPushMatrix();
            ofSetColor(ofColor::white);
            ofMultMatrix(getMatrix());
            spriteImage.draw(-spriteImage.getWidth() / 2, -spriteImage.getHeight() / 2.0);
            ofPopMatrix();
        }
        else
        {
            if (bHighlight) ofSetColor(ofColor::white);
            else ofSetColor(ofColor::green);
            TriangleShape::draw();
        }
    }

    float age() {
        return (ofGetElapsedTimeMillis() - birthtime);
    }

    void setImage(ofImage img) {
        spriteImage = img;
        bShowImage = true;
        width = img.getWidth();
        height = img.getHeight();
    }

    bool inside(vector<glm::vec3> p, glm::vec3 a, glm::mat4 T);

    void setSelected(bool state) { bSelected = state; }
    void setHighlight(bool state) { bHighlight = state; }
    bool isSelected() { return bSelected; }
    bool isHighlight() { return bHighlight; }

    
    glm::vec3 heading() {
        float angle = glm::radians(rot);
        glm::vec3 head = glm::normalize(glm::vec3(glm::sin(angle), -glm::cos(angle),0));
        return head;
    }
    
    float changeAngle(glm::vec3 plyrPos){
        glm::vec3 v = glm::normalize(plyrPos - pos);
        float turningAngle = glm::degrees(glm::orientedAngle(this->heading(), v, glm::vec3(0,0,1)));
        return rot + turningAngle;
    }

    bool bHighlight = false;
    bool bSelected = false;
    bool bShowImage = false;

    glm::vec3 velocity = glm::vec3(0, 0, 0);
    float birthtime = 0; // elapsed time in ms
    float lifespan = -1;  //  time in ms
    string name =  "UnammedSprite";
    float width = 40;
    float height = 40;
    
    
    ofImage spriteImage;
};

