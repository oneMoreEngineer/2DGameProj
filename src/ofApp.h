#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Emitter.h"
#include "Shape.h"

class Player {
public:
    Player() {}
    Player(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
        verts.push_back(p1);
        verts.push_back(p2);
        verts.push_back(p3);
    }
    void draw();
    glm::vec3 heading();
    glm::vec3 pos;
    glm::mat4 T;
    float rotation = 0.0;    // degrees
    glm::vec3 _scale = glm::vec3(1, 1, 1);
    vector<glm::vec3> verts;
};



class AgentEmitter : public Emitter {
public:

};


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
//    vector<Emitter *> emitters;
//    int numEmitters;

    Emitter  *creator = NULL;

    ofImage defaultImage;
    ofVec3f mouse_last;
    bool imageLoaded;

    bool bHide;
    ofxFloatSlider SpeedSlider;
    ofxIntSlider EnergySlider;
    ofxFloatSlider ScaleSlider;
    ofxFloatSlider rate;
    ofxFloatSlider life;
    ofxToggle shHeadingVec;
    ofxButton start;
    
    Player plyr;

    ofxPanel gui;

    bool movleft = false;
    bool movright = false;
    bool movup = false;
    bool movdown = false;
    bool firstStart;
    
    ofxToggle shSprite;
    ofImage image;
    ofImage background;
    int energy;
        
};
