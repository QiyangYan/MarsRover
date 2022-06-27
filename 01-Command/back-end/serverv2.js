//v2 server yet to test
//stores esp data into database and send as variable array to frontend (combined index.js and server.js)
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
// db.run(`CREATE TABLE Alien(alien_x, alien_y, alien_color)`);
// db.run(`CREATE TABLE Path(rover_x, rover_y)`);

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


app.listen(port,(err)=>err?console.log(err):console.log(`Server Running on port ${port}`)) 

//close database
// db.close((err)=>{
//     if (err) return console.log(err.message);
// })
