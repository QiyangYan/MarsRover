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
.then(AlienGet())
.then(PathGet())
.catch((err)=>{console.log(err.message)})

//create table
//db.run(`CREATE TABLE Alien(alien_x, alien_y, alien_color)`);
//db.run(`CREATE TABLE Path(rover_x, rover_y)`);

//insert row
const addAlien= `INSERT INTO Alien(alien_x, alien_y, alien_color) VALUES(?,?,?)`;
const addPath= `INSERT INTO Path(rover_x, rover_y) VALUES(?,?)`;

// db.run(addAlien,['30', '50','G'], (err)=>{
//     if (err) return console.log(err.message);
//     });

// db.run(addAlien,['100', '40','R'], (err)=>{
//     if (err) return console.log(err.message);
//     });
// db.run(addPath,['20', '20'], (err)=>{
//     if (err) return console.log(err.message);
//     });
// db.run(addPath,['40', '20'], (err)=>{
// if (err) return console.log(err.message);
// });
// db.run(addPath,['60', '20'], (err)=>{
//     if (err) return console.log(err.message);
//     });
// db.run(addPath,['80', '20'], (err)=>{
//     if (err) return console.log(err.message);
//     });

const sqlRemoveDup = `DELETE FROM Alien 
                    WHERE EXISTS (
                    SELECT 1 FROM Alien a2 
                    WHERE Alien.alien_x = a2.alien_x
                    AND Alien.alien_y = a2.alien_y
                    AND Alien.rowid > a2.rowid
                    );
                    SELECT * from Alien `;


//read from database
var alieninfo = {};
const readAlien = `SELECT * 
                    FROM Alien
                    WHERE rowid = (SELECT MAX(rowid) FROM Alien)`;
// db.all(readAlien,[],(err, rows)=>{
//     if (err) return console.log(err.message);
//     rows.forEach((row)=>{
//         alieninfo = row;
//     })
// })

var pathinfo = {};
const readPath = `SELECT * 
                    FROM Path
                    WHERE rowid = (SELECT MAX(rowid) FROM Path)`;
// db.all(readPath,[],(err, rows)=>{
//     if (err) return console.log(err.message);
//     rows.forEach((row)=>{
//         pathinfo = row;
//     })
// })

var distanceExplored = 3;
var displacementFromBase = 3;
var goBack = false;

var Command = {mode:'', command:''};
var espInfo = [{x_axis: 1, y_axis: 0, color:'', ball_x: '', ball_y: ''}];

function AlienGet(){
    db.all(readAlien,[],(err, rows)=>{
        if (err) return console.log(err.message);
        rows.forEach((row)=>{
            alieninfo = row;
        })
    })
    console.log(alieninfo);
    app.get('/frontend/data/alien', function(req, res) {
        res.set('Content-Type','application/json');
        res.send(alieninfo);
        console.log('front end alien get request received');
        console.log(alieninfo);
    });
}

function PathGet(){
    db.all(readPath,[],(err, rows)=>{
        if (err) return console.log(err.message);
        rows.forEach((row)=>{
            pathinfo = row;
        })
    })
    console.log(pathinfo);
    app.get('/frontend/data/path', function(req, res) {
        res.set('Content-Type','application/json');
        res.send(pathinfo);
        console.log('front end path get request received');
        console.log(pathinfo);
    });
}

// app.get('/frontend/data', function(req, res) {
//     res.set('Content-Type','application/json');
//     res.send(status);
//     console.log('front end get request received');
//     console.log(status.alienCoordinate[0].x);
// });


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
    // //removes duplicates
    // var info = espInfo.filter((item, index, self) => 
    // index === self. findIndex((t) => (
    //     t.ball_x === item.ball_x && t.ball_y === item.ball_y && t.color ===item.color
    // )))
    // espInfo = info;
    console.log(espInfo);

    //store data into database
    if(req.body.color !== ''){
        db.run(addAlien,[req.body.ball_x, req.body.ball_y,req.body.color], (err)=>{
            if (err) return console.log(err.message);
            console.log(req.body.ball_x);
            console.log(req.body.ball_y);
            console.log(req.body.color);
            console.log('an alien has been found');});
        db.all(sqlRemoveDup, [], (err) => {
            if (err) return console.log(err.message);
            console.log('a duplicate has been removed');
        })
    };
    db.run(addPath, [req.body.x_axis, req.body.y_axis], (err)=>{
            if(err) return console.log(err.message);
            console.log(req.body.x_axis);
            console.log(req.body.y_axis);
            console.log('a new rover position has been added');
    })
});


//close database
// db.close((err)=>{
//     if (err) return console.log(err.message);
// })

app.listen(port,(err)=>err?console.log(err):console.log(`Server Running on port ${port}`)) 

