//working server, without website
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
var goBack = false;

var Command = {mode:'', command:''};

var espInfo = [{x_axis: 20, y_axis: 20, color:'G', ball_x: '100', ball_y: '200'}];


app.get('/frontend/data', function(req, res) {
    res.set('Content-Type','application/json');
    console.log('front end post request received');
    res.send(espInfo);
    console.log(espInfo);
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
    console.log('---- esp post request received ----');
    espInfo.push(req.body);
    var info = espInfo.filter((item, index, self) => 
    index === self. findIndex((t) => (
        t.ball_x === item.ball_x && t.ball_y === item.ball_y && t.color ===item.color
    )))
    espInfo = info;
    console.log(espInfo);
});


app.listen(port,(err)=>err?console.log(err):console.log(`Server Running on port ${port}`)) 

