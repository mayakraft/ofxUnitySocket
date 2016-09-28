#include "ofApp.h"

#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"

//--------------------------------------------------------------
void ofApp::setup(){
	grabber.initGrabber(320, 240);
	camImage.allocate(320, 240, OF_IMAGE_COLOR);//OF_IMAGE_GRAYSCALE);

	isConnected = false;
	
	address = "http://127.0.0.1:3000";
	status = "not connected";
	socketIO.setup(address);
	ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);
	ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
}

stringstream ofApp::encode(ofBuffer buffer){
	// Convert the binary image data to string using base64 encoding
	stringstream ss;
	Poco::Base64Encoder b64enc(ss);
//	b64enc.setLineLength(0);
	b64enc << buffer;

	// here's the data
	ss.str();
//	cout << ss.str() << endl;
	
	return ss;
}

//void ofApp::encode(){
//	stringstream ss;
////	ofBuffer imageBuffer = camImage.getPixels();
//	
//	ofPixels px;
//	px.setFromPixels(camImage.getPixels(), camImage.getWidth(), camImage.getHeight(), camImage.getPixelsRef().getImageType());
//	
//	ofBuffer imageBuffer;
//	ofSaveImage(px, imageBuffer);
//
//
//	ss << imageBuffer;
//	Poco::Base64Encoder b64enc(ss);
////	b64enc << imageBuffer;
////	b64enc.close();
//	cout << &b64enc;
//}

//void thing(){
//	stringstream ss;
//	ss << base64ImageData;
//	Poco::Base64Decoder b64in(ss);
//	
//	ofBuffer buffer;
//	b64in >> buffer;
//	
//	image.loadImage(buffer);
//}

//--------------------------------------------------------------
void ofApp::update(){
	static unsigned long sec = ofGetElapsedTimef();
	if(ofGetElapsedTimef() != sec){
		sec = ofGetElapsedTimef();
	}
	
	grabber.update();
	if(grabber.isFrameNew()) {
		camImage.setFromPixels(grabber.getPixels());
		camImage.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapStringHighlight(ofApp::status, 20, 20);

	camImage.draw(0, 60, 640, 480);
}

void ofApp::onConnection () {
	isConnected = true;
	bindEvents();
}

void ofApp::bindEvents () {
	std::string serverEventName = "server-event";
	socketIO.bindEvent(serverEvent, serverEventName);
	ofAddListener(serverEvent, this, &ofApp::onServerEvent);
	
	std::string pingEventName = "ping";
	socketIO.bindEvent(pingEvent, pingEventName);
	ofAddListener(pingEvent, this, &ofApp::onPingEvent);
}

void ofApp::gotEvent(string& name) {
	status = name;
}

void ofApp::onServerEvent (ofxSocketIOData& data) {
	ofLogNotice("ofxSocketIO", data.getStringValue("stringData"));
	ofLogNotice("ofxSocketIO", ofToString(data.getIntValue("intData")));
	ofLogNotice("ofxSocketIO", ofToString(data.getFloatValue("floatData")));
	ofLogNotice("ofxSocketIO", ofToString(data.getBoolValue("boolData")));
}

void ofApp::onPingEvent (ofxSocketIOData& data) {
	ofLogNotice("ofxSocketIO", "ping");
	std::string pong = "pong";
	std::string param = "foo";
	socketIO.emit(pong, param);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == ' '){
		ofPixels px;
		px.setFromPixels(camImage.getPixels(), camImage.getWidth(), camImage.getHeight(), camImage.getPixelsRef().getImageType());
		
		ofBuffer imageBuffer;
		ofSaveImage(px, imageBuffer);
		stringstream b64Image = encode(imageBuffer);
		std::string eventName = "image";
		std::string imgString = "";
		imgString = "data:image/jpeg;base64," + b64Image.str();
		imgString.erase(std::remove(imgString.begin(), imgString.end(), '\n'), imgString.end());
		imgString.erase(std::remove(imgString.begin(), imgString.end(), '\r'), imgString.end());
		cout << "sending emit: " << eventName << endl;
		socketIO.emit(eventName, imgString);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){ }
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){ }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){ }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){ }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }
