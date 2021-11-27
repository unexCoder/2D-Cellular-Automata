#include "ofApp.h"
#include <algorithm>

#define NUM_ITERATIONS 20

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    fill = true;
    
    std::vector<std::vector<bool>> ca = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0}};
    
    
    code = 174826;
    for (int i = 0;i < NUM_ITERATIONS; i++) {
        ca = cellAutom_2D(ca,code);
        autom.push_back(ca);
    }
    
    ofEnableLighting();
    light.setAmbientColor(ofColor::white);
    
    material.setAmbientColor(ofFloatColor(0.1,0.1,0.1,1.0));
    material.setDiffuseColor(ofFloatColor(0.8,0.8,0.1,1.0));
    material.setSpecularColor(ofFloatColor(0.8,0.9,0.5,1.0));
    material.setEmissiveColor(ofFloatColor(0.8,0.1,0.5,1.0));
    material.setShininess(120);

    // minimal cam proyection setup
    cam.setAspectRatio(16/9); // aspect ratio
    cam.setNearClip(0.f);     // near clip plane distance
    cam.setFarClip(10000.f);  // far clip plane distance
    cam.setFov(45); // default cam Field of View in degrees
    
    camPosition = glm::vec3(0.f,0.f,1000.f);
    cam.setPosition(camPosition);
    
#ifdef TARGET_OPENGLES
    shader.load("shaders_gles/noise.vert","shaders_gles/noise.frag");
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
    }else{
        shader.load("shaders/noise.vert", "shaders/noise.frag");
    }
#endif
    
    mode = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetGlobalAmbientColor(ofColor::white);
    
//    emissiveColor.setSaturation(1.f);emissiveColor.setBrightness(1.f);
//    emissiveColor.setHue(ofMap(ofGetMouseX(),ofGetWidth()/3,ofGetWidth()/2,0.f,1.f));
//    material.setEmissiveColor(emissiveColor);
    
    float x = ofMap(ofGetMouseX(),0,ofGetWidth(),-ofGetWidth()/3,ofGetWidth()/3);
    float z = ofMap(ofGetMouseY(),0,ofGetHeight(),-ofGetHeight(),ofGetHeight());

    camPosition = glm::vec3(x,100.f,z+1000.f);
    cam.setPosition(camPosition);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofLight();

    cam.begin();
    ofEnableDepthTest();

    light.enable();

    if (!fill) {
        ofNoFill();
    } else {
        ofFill();
    }
    // draw automata
    for(int i = autom.size()-1; i > autom.size()-NUM_ITERATIONS; i--) {
        cout << endl;
        ofPushMatrix();
        ofTranslate(glm::vec3(0.f,-(i-autom.size()-1)*10.f,0.f));
        for(int j = 0; j < autom[i].size(); j++) {
            ofPushMatrix();
            ofTranslate(glm::vec3(-i*10.f,0.f,-i*10.f));
            for(int k = 0; k < autom[i][j].size(); k++) {
                bool cell = autom[i][j][k];
                if(cell) {
                    
                    //float coin = ofRandom(1.f);
                    //if (coin <= 0.99) {
                    if (mode == 0) {
                        material.begin();
                        ofDrawBox((j*10.f)-5,0,(k*10.f)-5,10,10,10);
                        material.end();
                    } else if (mode == 1) {
                        if (((k%5==0)&&(j%9==0))||((k%5==0)&&(j%3==0))) {
                            shader.begin();
                            ofDrawBox((j*10.f)-5,0,(k*10.f)-5,10,10,10);
                            shader.end();
                        } else {
                            material.begin();
                            ofDrawBox((j*10.f)-5,0,(k*10.f)-5,10,10,10);
                            material.end();
                        }
                    } else if (mode == 2) {
                        shader.begin();
                        ofDrawBox((j*10.f)-5,0,(k*10.f)-5,10,10,10);
                        shader.end();

                    }
                }
            }
            ofPopMatrix();
        }
        ofPopMatrix();
    }
    //
    light.disable();

    ofDisableDepthTest();
    cam.end();
    
    // win title
    std::ostringstream ss;
    ss << ofGetFrameRate();
    std::string s(ss.str());
    ofSetWindowTitle(s);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case OF_KEY_RIGHT:
        break;
        case OF_KEY_LEFT:
            break;
        case OF_KEY_UP:
            break;
        case OF_KEY_DOWN:
            break;
    
        case 'M':
        case 'm':
            mode++; mode = mode % 3;
            break;
        case 'W':
        case 'w':
            fill = !fill;
            break;
        case ' ':
            break;
        case 'C':
        case 'c':
            break;
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'H':
        case 'h':
            break;
        case 'I':
        case 'i':
            break;
        case 'Y':
        case 'y':
            break;
        case 'Q':
        case 'q':
            std::vector<std::vector<bool>> ca = {
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,1,1,1,1,1,1,1,1,1,1,1,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0}};
            autom.clear();
            code = ofRandom(262144);
            for (int i = 0;i < NUM_ITERATIONS; i++) {
                ca = cellAutom_2D(ca,code);
                autom.push_back(ca);
            }
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

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

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
std::vector<std::vector<bool>> ofApp::cellAutom_2D(std::vector<std::vector<bool>> input, int rule ) {
    // convert rule to binary and hold it into ruleset bitset
    bitset<18> ruleset = rule;                      // ruleset
    
    for (int i = 0; i < input.size(); i++) {
        input[i].push_back(0);
        input[i].insert(input[i].begin(),0);
    }
    
    std::vector<bool> insert (input.size()+2,0);
    input.push_back(insert);
    input.insert(input.begin(),insert);
    
    // calculate new generation and hold it in output vector
    std::vector<std::vector<bool>> out;
    out.resize(input.size());
    std::copy (input.begin(),input.end(),out.begin());
    
    for (int i = 1; i < input.size()-1; i++) {
        for (int j = 1; j < input[i].size()-1; j++) {
            
            int n = input[i-1][j] + input[i+1][j] + input[i][j-1] + input[i][j+1] +
            input[i-1][j-1] + input[i+1][j-1] + input[i+1][j+1] + input[i-1][j+1];
            
            if (input[i][j]==0) {
                out[i][j] = ruleset[n*2];
            } else {
                out[i][j] = ruleset[(n*2)+1];
            }
        }
    }
    // voualá
    return out;
}
