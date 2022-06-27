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

var distanceExplored = 3;
var displacementFromBase = 3;
var goBack = false;

var Command = {mode:'', command:''};

var espInfo = [];


app.get('/frontend/data', function(req, res) {
    res.set('Content-Type','application/json');
    console.log('front end get request received');
    res.send(espInfo);
});

app.post('/frontend/post', (req, res) => {
    res.send("web POST request called")
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
    console.log('new message: '+req.body);
    espInfo.push(req.body);
    var info = espInfo.filter((item, index, self) => 
    index === self. findIndex((t) => (
        t.x_axis === item.x_axis && t.y_axis === item.y_axis 
        && t.ball_x === item.ball_x && t.ball_y === item.ball_y && t.color ===item.color
    )))
    espInfo = info;
    console.log("inside post:"+ espInfo);
});

app.listen(port,(err)=>err?console.log(err):console.log(`Server Running on port ${port}`)) 

