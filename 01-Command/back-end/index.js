//working server, needs more endpoints and processing esp json to website capatable json

const express = require('express');
const bodyParser = require('body-parser');
const sqlite3 = require('sqlite3').verbose();
var cors = require('cors');
var app = express();
var port = 9000;
//initiate database
const db = new sqlite3.Database('./mock.sqlite', sqlite3.OPEN_READWRITE,(err)=>{
    if (err) return console.log(err.message);
    console.log('database connection successful')
})
//create table
//db.run(`CREATE TABLE alien(alien_x, alien_y, alien_color)`);
//db.run(`CREATE TABLE path(rover_x, rover_y)`);
// //insert row
// const sql= `INSERT INTO alien(alien_x, alien_y, alien_color) VALUES(?,?,?)`;

// db.run(sql,['1', 'G', '{x: 1, y:1}'], (err)=>{
//     if (err) return console.log(err.message);
//     console.log('a new row has been created')});

// const sql = `SELECT * from alien`;

// db.all(sql, [], (err, rows) => {
//     if (err) return console.log(err.message);
//     rows.forEach((row)=>{
//         console.log(row);
//     })
// })
//close database
// db.close((err)=>{
//     if (err) return console.log(err.message);
// })

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
var espInfo = [{x_axis: 1, y_axis: 0, color:'', ball_x: '', ball_y: ''}];

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
    espInfo.push(req.body);
    //removes duplicates
    var info = espInfo.filter((item, index, self) => 
    index === self. findIndex((t) => (
        t.ball_x === item.ball_x && t.ball_y === item.ball_y && t.color ===item.color
    )))
    espInfo = info;
    console.log(espInfo);

    //if(req.body.color !== ''){
    // const sql= `INSERT INTO alien(alien_x, alien_y, alien_color) VALUES(?,?,?)`,
    //[req.body.ball_x, req.body.ball_y,req.body.color],(err)=>{
    //     if (err) return console.log(err.message);
    //     console.log('a new row has been created')};
    //}
    
});

app.listen(port,(err)=>err?console.log(err):console.log(`Server Running on port ${port}`)) 

