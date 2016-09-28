var express = require('express');
var app = express();
var server = app.listen(process.env.PORT || 3000);
var socket = require('socket.io');
var io = socket(server);

app.use(express.static('public'));

io.sockets.on('connection', newConnection);

function newConnection(socket){
	console.log('new connection: ' + socket.id);

	// get a message from 1 client, send it out to all the others
	socket.on('image', function(data){
		console.log('somebody sent an image');
		// io.broadcast('image', data);
		io.emit('image', data);
	});
	socket.on('disconnect', function(){
		console.log('somebody disconnected');
	});
}