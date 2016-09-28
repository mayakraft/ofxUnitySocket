#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxSocketIO.h"
#include "ofxSocketIOData.h"

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
	
	
	ofVideoGrabber grabber;
	ofImage camImage;
	
	// SOCKET IO
	void gotEvent(std::string& name);
	void onServerEvent(ofxSocketIOData& data);
	void onPingEvent(ofxSocketIOData& data);
	
	ofxSocketIO socketIO;
	
	bool isConnected;
	void onConnection();
	void bindEvents();
	ofEvent<ofxSocketIOData&> serverEvent;
	ofEvent<ofxSocketIOData&> pingEvent;
	
	std::string address;
	std::string status;
	
	stringstream encode(ofBuffer buffer);

};
