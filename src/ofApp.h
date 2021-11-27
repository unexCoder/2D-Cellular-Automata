#pragma once

#include "ofMain.h"

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
    
    std::vector<std::vector<bool>> cellAutom_2D(std::vector<std::vector<bool>> input, int ruleset);
    
    std::vector<std::vector<std::vector<bool>>> autom;
    int code;
    int mode;
        
    ofLight light;
    ofMaterial material;
    bool fill;
    
    ofFloatColor emissiveColor,ambientColor, difusseColor, specularColor;
    
    ofCamera cam;
    glm::vec3 camPosition,camOrientation,camVelocity;
    
    ofShader shader;
};
