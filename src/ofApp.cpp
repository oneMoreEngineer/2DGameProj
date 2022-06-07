#include "ofApp.h"

glm::vec3 Player::heading(){
    float angle = glm::radians(rotation);
    glm::vec3 head = glm::normalize(glm::vec3(glm::sin(angle), -glm::cos(angle),0));
    return head;
}

void Player::draw(){
    glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
    glm::mat4 rotM = glm::rotate(glm::mat4(1.0), glm::radians(rotation),
    glm::vec3(0, 0, 1));
    glm::mat4 scaleM = glm::scale(glm::mat4(1.0), _scale);
    T = trans * rotM * scaleM;
    ofSetColor(ofColor::red);
    ofFill();
    ofPushMatrix();
    ofMultMatrix(T);
    ofDrawTriangle(verts[0], verts[1], verts[2]);
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);

    // create an image for sprites being spawned by emitter
    //
    if (defaultImage.load("images/Drawing.png")) {
        defaultImage.resize(250, 140);
        imageLoaded = true;
    }
    else {
        cout << "Can't open image file" << endl;
        ofExit();
    }


    plyr =  Player(glm::vec3(-50, 50, 0), glm::vec3(50, 50, 0), glm::vec3(0,
                                                                         -50, 0));
    plyr.pos = glm::vec3(ofGetWindowWidth()/2.0, ofGetWindowHeight()/2.0, 0);
    plyr.rotation = 0;
    plyr.draw();
    creator = new AgentEmitter();

    creator->pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
    creator->drawable = false;
  ;
    
    gui.setup();
    gui.add(shHeadingVec.setup("Heading Vector", false));
    gui.add(SpeedSlider.setup("Speed", 200, 0, 500));
    gui.add(ScaleSlider.setup("Scale", 1, 0.5, 5));
    gui.add(rate.setup("rate", 1, 1, 10));
    gui.add(life.setup("life", 5, .1, 10));
    gui.add(shSprite.setup("Show Sprite", false));
    gui.add(EnergySlider.setup("Energy", 3, 1, 10));
    gui.add(start.setup("Start"));
    
    
    
    bHide = false;
    firstStart = true;
    image.load("images/player.png");
    image.resize(100, 130);
   // image.rotate90(3);
    plyr.draw();
    creator->energy = EnergySlider;
    
    background.load("images/background.jpeg");
    background.resize(ofGetWindowWidth(), ofGetWindowHeight());

}

//--------------------------------------------------------------
void ofApp::update() {

    if (start){
        firstStart = false;
        creator->start();
        creator->energy = EnergySlider;
    }
    creator->setRate(rate);
    creator->setLifespan(life * 1000);    // convert to milliseconds
    //turret->setVelocity(ofVec3f(velocity->x, velocity->y, velocity->z));
    creator->update(plyr.pos, plyr.verts, plyr.T);

    if (plyr.pos.x <= 0){
        plyr.pos.x = 0;
    }
    if (plyr.pos.x >= ofGetWindowWidth()){
        plyr.pos.x = ofGetWindowWidth();
    }
    if (plyr.pos.y <= 0){
        plyr.pos.y = 0;
    }
    if (plyr.pos.y >= ofGetWindowHeight()){
        plyr.pos.y = ofGetWindowHeight();
    }
    
    if (movright){
        plyr.rotation += 1;
    }
    if (movleft){
        plyr.rotation -= 1;
    }
    if (movup){
        plyr.pos += (float) SpeedSlider/60 * plyr.heading();
    }
    if (movdown){
        plyr.pos -= (float) SpeedSlider/60 * plyr.heading();
    }
    
    
    if (creator->energy == 0){
        ofDrawBitmapString("GAME OVER", ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2));
        creator->stop();
    }
    
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    background.resize(ofGetWindowWidth(), ofGetWindowHeight());
    background.draw(0, 0);
    creator->draw();
    plyr._scale.x = ScaleSlider;
    plyr._scale.y = ScaleSlider;
    plyr._scale.z = ScaleSlider;
    
    if (creator->started){
        ofSetColor(ofColor::white);
        ofDrawBitmapString("current energy: " + ofToString(creator->energy), ofGetWidth() - 250, 10);
        ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), ofGetWidth() - 250, 30);
    }
    if ( firstStart){
        ofSetColor(ofColor::white);
        ofDrawBitmapString("To start the game: press Start" , ofPoint(ofGetWindowWidth() / 2 - 200, ofGetWindowHeight() / 2) + 100);
    }
    
    if (!bHide) {
        gui.draw();
    }
    if (shHeadingVec) {
        ofSetColor(ofColor::green);
        ofDrawLine(plyr.pos, plyr.pos + 75 * plyr.heading());
    }
    
    if (shSprite == true){
        creator->setChildImage(defaultImage);
        glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(plyr.pos));
        glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(plyr.rotation),
        glm::vec3(0, 0, 1));
        glm::mat4 scale = glm::scale(glm::mat4(1.0), plyr._scale);
        plyr.T = trans * rot * scale;
        image.setAnchorPoint(plyr.pos.x, plyr.pos.y);
        ofSetColor(ofColor::white);
        ofPushMatrix();
        ofMultMatrix(plyr.T);
        image.draw(plyr.pos.x - image.getWidth()/2 - 8, plyr.pos.y - image.getHeight()/2);
        ofPopMatrix();
        
    } else {
        creator->haveChildImage = false;
        plyr.draw();
    }
    
    if (creator->energy == 0){
        ofSetColor(ofColor::white);
        ofDrawBitmapString("GAME OVER", ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2) - 100);
        ofDrawBitmapString("Press R to restart", ofPoint(ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2) - 50);
    }
}


//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

void ofApp::keyPressed(int key) {
    switch (key) {
    case 'F':
    case 'f':
        ofToggleFullscreen();
        break;
    case 'H':
    case 'h':
        bHide = !bHide;
        break;
    case 'r':
        setup();
    }
    if (key == OF_KEY_RIGHT){
        movright = true;
    }
    if (key == OF_KEY_LEFT){
       movleft = true;
    }
    if (key == OF_KEY_UP){
       movup = true;

    }
    if (key == OF_KEY_DOWN){
       movdown = true;
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
    
    case OF_KEY_ALT:
        break;
    case OF_KEY_CONTROL:
        break;
    case OF_KEY_SHIFT:
        break;
    }
    if (key == OF_KEY_RIGHT){
        movright = false;
    }
    if (key == OF_KEY_LEFT){
       movleft = false;
    }
    if (key == OF_KEY_UP){
       movup = false;
    }
    if (key == OF_KEY_DOWN){
       movdown = false;
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

