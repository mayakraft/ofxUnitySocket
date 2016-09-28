# openFrameworks & Unity

Send data from openFrameworks to Unity via Socket.io, fast enough to be able to send low-res video

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

# notes

this uses [unity-socket.io](https://github.com/fpanettieri/unity-socket.io-DEPRECATED), which is depricated but works for now. (It's already included in this project)

also this isn't in the standard format of an openFrameworks ofx extension. it can be but it's more of an example project right now.