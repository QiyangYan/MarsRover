//working server, needs more endpoints and processing esp json to website capatable json

const express = require('express');
const bodyParser = require('body-parser');
var cors = require('cors');
var app = express();
var port = 9000;

var corsOptions = {
    origin:['http://localhost:3000', 'http://localhost:9000'],
    optionsSuccessStatus: 200
}

app.use(cors(corsOptions));
app.use(bodyParser.json());

/*{
    speed: 2, //float
    distanceExplored: 3, //float
    displacementFromBase: 3, //float
    roverCoordinate : {x:0, y:3},
    alienCoordinate : [{x:5, y:2, color:''}, {x:7, y:4, color: ''}],
    infraCoordinate : [{x:1, y:3}, {x:2, y:5}]
    goBack: false //boolean, depends on displacement and battery level
}*/

var distanceExplored = 3;
var displacementFromBase = 3;
var status = {roverCoordinate : {x:0, y:3},
 alienCoordinate : [{x:5, y:2, color:''}, {x:7, y:4, color: ''}],
 infraCoordinate : [{x:1, y:3}, {x:2, y:5}]}
var batteryCharging = false;
var goBack = false;

var Command = {mode:'', command:''};
var alienInfo = [{distance: 1, angle: 0, color:''},{distance: 1, angle: 0, color:'G'},{distance: 1, angle: 0, color:''}];

app.get('/frontend/data/map', function(req, res) {
    res.set('Content-Type','application/json');
    res.send(info);
    console.log('front end get request received');
    console.log(status.alienCoordinate[0].x);
});



app.get('/frontend/data', function(req, res) {
    res.set('Content-Type','application/json');
    res.send(status);
    console.log('front end get request received');
    console.log(status.alienCoordinate[0].x);
});


app.post('/frontend/post', (req, res) => {
    res.send("web POST Request Called")
    console.log('front end post request received');
    Command.mode = req.body.mode;
    Command.command = req.body.command;
    console.log(Command);
  });

app.get('/esp/commands/get', function(req,res) {
    res.set('Content-Type', 'application/json');
    console.log('esp get request received');
    res.send(Command);
});

app.post('/esp/commands/post', function(req,res) {
    console.log('esp post request received');
    console.log(req.body.distance);
    console.log(req.body.angle);
    console.log(req.body.color);
    alienInfo.push(req.body);
    //removes duplicates
    var info = alienInfo.filter((item, index, self) => 
    index === self. findIndex((t) => (
        t.distance === item.distance && t.angle === item.angle && t.color ===item.color
    )))
    alienInfo = info;
    console.log(alienInfo);
});

app.listen(port,(err)=>err?console.log(err):console.log(`Server Running on port ${port}`)) 


/*
//import Node Package Management package
const express = require('express');
//const mysql = require('mysql');
const cors = require('cors');
const bodyParser = require('body-parser');

var app = express();
var port = 3100;
var corsOptions = {
    origin:['http://localhost:3100', 'http://localhost:3000'],
    optionsSuccessStatus: 200
}

app.use(cors(corsOptions));

//app.use(bodyParser.json());

//config conncection to database
// const connection = mysql.createConnection({ host:"localhost",
// database:"cps_ecc_22",
// user:"root",
// password:"" })




// Connecting to databese
// connection.connect(err=>{err?console.log(err):console.log("Connection to database OK")})

// Once connected to database, we create a ROUTE that specifies the REQUEST type or method
// app.get('/data',(req,res)=>{
//     connection.query('SELECT * FROM iot',(err,rows)=>{
//         err?res.send(err):res.send(rows) 
//     })
// })

app.get('/', function(req, res) {
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end('Hello, Server!');
});

app.post('/post', (req, res) => {
    //res.send("POST Request Called")
    console.log('post request received');
    console.log(req.body.str1);
  })

app.listen(port,(err)=>err?console.log(err):console.log(`Server Running on port ${port}`)) 

*/