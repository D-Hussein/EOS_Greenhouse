


//Loading modules
const execFile = require('child_process').execFile;
var http = require('http');
var fs = require('fs');
var path = require('path');

// Initialize the server on port 8888
var server = http.createServer(function (req, res) {
    // requesting files
    var file = '.'+((req.url=='/')?'/index.html':req.url);
    var fileExtension = path.extname(file);
    var contentType = 'text/html';
    // Uncoment if you want to add css to your web page
    
    if(fileExtension == '.css'){
        contentType = 'text/css';
    }
    fs.exists(file, function(exists){
        if(exists){
            fs.readFile(file, function(error, content){
                if(!error){
                    // Page found, write content
                    res.writeHead(200,{'content-type':contentType});
                    res.end(content);
                }
            });
        }
        else{
            // Page not found
            res.writeHead(404);
            res.end('Page not found');
        }
    });
}).listen(8888, console.log("Server Running ..."));

// Loading socket io module.
var io = require('socket.io').listen(server);

// When communication is established
io.on('connection', function (socket) {
    
    
	
	// On call from Browser for temperature
    socket.on('temp', function getTemp() {
		const child = execFile('/home/debian/Green',['t_h','temp'],(error, stdout, stderr) => {
	//	if(error) {
	//		console.error('stderr', stderr);
	//		throw error;
	//	}
		console.log(stdout);
		
		// Create and send JSON object to browser
		var data = {temperature: stdout};
		var dataJSON = JSON.stringify(data);
		io.emit('tempData', dataJSON);
		});
	});
	
	////
	
	// On call from Browser for humidity
    socket.on('hum', function gethum() {
		const child = execFile('/home/debian/Green',['t_h','hum'],(error, stdout, stderr) => {
	//	if(error) {
	//		console.error('stderr', stderr);
	//		throw error;
	//	}
		console.log(stdout);
		
		// Create and send JSON object to browser
		var data = {humidity: stdout};
		var dataJSON = JSON.stringify(data);
		io.emit('humData', dataJSON);
		});
	});
	
	
	// On call from Browser for heater
    socket.on('heatOn', function turnOn() {
		const child = execFile('/home/debian/Green',['heater','on'],(error, stdout, stderr) => {
	//	if(error) {
	//		console.error('stderr', stderr);
	//		throw error;
	//	}
		console.log(stdout);
		
		// Create and send JSON object to browser
		var data = {heater1: stdout};
		var dataJSON = JSON.stringify(data);
		io.emit('heatOn', dataJSON);
		});
	});
	socket.on('heatOff', function turnOff() {
		const child = execFile('/home/debian/Green',['heater','off'],(error, stdout, stderr) => {
	//	if(error) {
	//		console.error('stderr', stderr);
	//		throw error;
	//	}
		console.log(stdout);
		
		// Create and send JSON object to browser
		var data = {heater0: stdout};
		var dataJSON = JSON.stringify(data);
		io.emit('heat', dataJSON);
		});
	});
	
	// On call from Browser for light
    socket.on('lightOn', function turnLightOn() {
		const child = execFile('/home/debian/Green',['light','60'],(error, stdout, stderr) => {
	//	if(error) {
	//		console.error('stderr', stderr);
	//		throw error;
	//	}
		console.log(stdout);
		
		// Create and send JSON object to browser
		var data = {light1: stdout};
		var dataJSON = JSON.stringify(data);
		io.emit('lightOn', dataJSON);
		});
	});
	socket.on('lightOff', function turnLightOff() {
		const child = execFile('/home/debian/Green',['light','3'],(error, stdout, stderr) => {
	//	if(error) {
	//		console.error('stderr', stderr);
	//		throw error;
	//	}
		console.log(stdout);
		
		// Create and send JSON object to browser
		var data = {light0: stdout};
		var dataJSON = JSON.stringify(data);
		io.emit('lightOff', dataJSON);
		});
	});
	socket.on('lightOffOff', function turnLightOffOff() {
		const child = execFile('/home/debian/Green',['light','0'],(error, stdout, stderr) => {
	//	if(error) {
	//		console.error('stderr', stderr);
	//		throw error;
	//	}
		console.log(stdout);
		
		// Create and send JSON object to browser
		var data = {light00: stdout};
		var dataJSON = JSON.stringify(data);
		io.emit('lightOffOff', dataJSON);
		});
	});
	
	
	///////
		
	 ////Servo ToDo 
	
socket.on('servo', function wind() {
		
		//ServoVars

var b = require('bonescript');
var SERVO = 'P9_14';
var duty_min = 0.03;
var position = 0;
var increment = 0.1;


b.pinMode(SERVO, b.OUTPUT);
// compute and adjust duty_cycle based on
    // desired position in range 0..1
    var duty_cycle = (position*0.115) + duty_min;
    b.analogWrite(SERVO, duty_cycle, 60,function scheduleNextUpdate() {
    // adjust position by increment and 
    // reverse if it exceeds range of 0..1
    position = position + increment;
    if(position < 0) {
        position = 0;
        increment = -increment;
    } else if(position > 1) {
        position = 1;
        increment = -increment;
    }
    
});
    console.log("Duty Cycle: " + 
        parseFloat(duty_cycle*100).toFixed(1) + " %");   
//updateDuty();




	
	});

	
	
});

	