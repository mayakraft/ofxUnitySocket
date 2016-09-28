var socket = io();

socket.on('image', function(data){
	console.log('somebody sent an image');
	var img = new Image();
	img.src = data;
	img.onload = start;
	function start(){
		var canvas = document.getElementById("canvas");
		var context = canvas.getContext("2d");
		var aspect = img.width / img.height;
		context.drawImage(img, 0, 0, 640, 640 / aspect);
	}
});

function didSelectFile() {
	var preview = document.querySelector('img');
	var file    = document.querySelector('input[type=file]').files[0];
	var reader  = new FileReader();

	reader.addEventListener("load", function () {
		preview.src = reader.result;
		socket.emit('image', reader.result);
	}, false);

	if (file) {
		reader.readAsDataURL(file);
	}
}