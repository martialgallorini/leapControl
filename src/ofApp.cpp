#include "ofApp.h"

/* Note on OS X, you must have this in the Run Script Build Phase of your project.
 where the first path ../../../addons/ofxLeapMotion/ is the path to the ofxLeapMotion addon.
 cp -f ../../addons/ofxLeapMotion2/libs/lib/osx/libLeap.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/libLeap.dylib"; install_name_tool -change ./libLeap.dylib @executable_path/libLeap.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME";
 If you don't have this you'll see an error in the console: dyld: Library not loaded: @loader_path/libLeap.dylib
 */

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    
    bDetected = false;
    
    oscSender.setup("localhost", 9001);
    
    // keep analysing hands even if app has not the focus
    leap.setReceiveBackgroundFrames(true);
    
    leap.open();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    fingersFound.clear();
    
    simpleHands = leap.getSimpleHands();
    
    if(leap.isFrameNew()) {
        
        if(simpleHands.size()) {
            leap.setMappingX(-100, 100, 0.f, 1.f);
            leap.setMappingY(90, 350, 1.f, 0.f);
            
            ofxOscMessage m;
            
            if(bDetected == false) {
                bDetected = true;
                m.setAddress("/hand/detected");
                m.addBoolArg(bDetected);
                oscSender.sendMessage(m);
            }
            
            // send only first detected hand position. More hands are ignored
            ofPoint pos = simpleHands.at(0).handPos;
            
            m.clear();
            m.setAddress("/hand/x");
            m.addFloatArg(pos.x);
            oscSender.sendMessage(m);
            
            m.clear();
            m.setAddress("/hand/y");
            m.addFloatArg(pos.y);
            oscSender.sendMessage(m);
        }
        else {
            if(bDetected == true) {
                bDetected = false;
                ofxOscMessage m;
                m.setAddress("/hand/detected");
                m.addBoolArg(bDetected);
                oscSender.sendMessage(m);
            }
        }
    }
    
    leap.markFrameAsOld();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < simpleHands.size(); i++) {
        ofPoint pos = simpleHands.at(i).handPos;
        ofDrawSphere(pos.x * ofGetWidth(),pos.y * ofGetHeight(), 10);
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    leap.close();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
