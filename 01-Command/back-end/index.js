//working server, needs connection from server database to website
const express = require('express');
const bodyParser = require('body-parser');
const sqlite3 = require('sqlite3').verbose();
var cors = require('cors');
var app = express();
var port = 9000;
var corsOptions = {
    origin:['http://localhost:3000', 'http://localhost:9000'],
    optionsSuccessStatus: 200
}
app.use(cors(corsOptions));
app.use(bodyParser.json());


//initiate database
const db = new sqlite3.Database('./data.sqlite', sqlite3.OPEN_READWRITE,(err)=>{
    if (err) return console.log(err.message);
    console.log('database connection successful')
})

//create table
//db.run(`CREATE TABLE Alien(alien_x, alien_y, alien_color)`);
//db.run(`CREATE TABLE Path(rover_x, rover_y)`);

//insert row
const addAlien= `INSERT INTO Alien(alien_x, alien_y, alien_color) VALUES(?,?,?)`;
const addPath= `INSERT INTO Path(rover_x, rover_y) VALUES(?,?)`;

const sqlRemoveDup = `DELETE FROM Alien 
                    WHERE EXISTS (
                    SELECT 1 FROM Alien a2 
                    WHERE Alien.alien_x = a2.alien_x
                    AND Alien.alien_y = a2.alien_y
                    AND Alien.rowid > a2.rowid
                    );
                    SELECT * from Alien `;
var alieninfo = [];
//read from database
const readAlien = 'SELECT * FROM Alien';
db.all(readAlien,[],(err, rows)=>{
    if (err) return console.log(err.message);
    rows.forEach((row)=>{
        alieninfo.push(row);
    })
    console.log(alieninfo);
})

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
//var espInfo = [{x_axis: 1, y_axis: 0, color:'', ball_x: '', ball_y: ''}];

app.get('/frontend/data/alien', function(req, res) {
    res.set('Content-Type','application/json');
    res.send(info);
    console.log('front end get request received');
    console.log(status.alienCoordinate[0].x);
});

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
    // espInfo.push(req.body);
    // //removes duplicates
    // var info = espInfo.filter((item, index, self) => 
    // index === self. findIndex((t) => (
    //     t.ball_x === item.ball_x && t.ball_y === item.ball_y && t.color ===item.color
    // )))
    // espInfo = info;
    // console.log(espInfo);

    //store data into database
    if(req.body.color !== ''){
        db.run(addAlien,[req.body.ball_x, req.body.ball_y,req.body.color], (err)=>{
            if (err) return console.log(err.message);
            console.log('an alien has been found');});
        db.all(sqlRemoveDup, [], (err) => {
            if (err) return console.log(err.message);
            console.log('a duplicate has been removed');
        })
    };
    db.run(addPath, [req.body.x_axis, req.body.y_axis], (err)=>{
            if(err) return console.log(err.message);
            console.log('a new rover position has been added');
    })
});


//close database
db.close((err)=>{
    if (err) return console.log(err.message);
})

app.listen(port,(err)=>err?console.log(err):console.log(`Server Running on port ${port}`)) 

