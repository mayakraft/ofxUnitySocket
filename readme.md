# openFrameworks Unity Socket.io

Send data from openFrameworks to Unity via Socket.io. Fast enough to be able to send low-res video.

# setup

* download and install [ofxSocketIO](https://github.com/soixantecircuits/ofxSocketIO)
* move the openFrameworks folder into your sketches folder
* run `npm install` then `node server.js` to begin server

# configure

manage ip and ports in 3 locations:

* __NODE__ port in `server.js`
* __OpenFrameworks__ port and IP in `ofApp.cpp`
* __Unity__ port and IP in `/Assets/SocketIO/Scripts/SocketIO/SocketIOComponents.cs` or in GameController scene object info panel.

current settings: port is set to 3000, sending across a LAN, and the computer running OF is also running the Node server.