//draws the map, still going
import React, {useState, useEffect} from 'react';
import {Stage, Layer, Circle, Rect, Line, Image} from 'react-konva';

// roverCoordinate : {x:0, y:3},
// alienCoordinate : [{x:5, y:2, color:''}, {x:7, y:4, color: ''}],
// infraCoordinate : [{x:1, y:3}, {x:2, y:5}]

const left = 50;
const top = 100;
var aliens = [{x:50, y:20, color:'red'}, {x:70, y:40, color: 'blue'}]
var infras = [{x:100, y:30}, {x:20, y:50}]
var poles = [{x:200, y:10}, {x:40, y:60}]
var positions = [{x:0,y:0},{x:5,y:0},{x:20,y:0},{x:30,y:0},{x:30,y:15}]
//var espInfo = [{x_axis: 1, y_axis: 0, color:'', ball_x: '', ball_y: ''}];

// const [data, setData] = useState({});
// //const alienImage =  useImage('https://www.indiewire.com/wp-content/uploads/2021/06/Yoda.png');
// var aliens = data.aliens;
// var infras = data.infras;
// var towers = data.towers;
// var positions = data.path;

// const callAPI = () =>{
//   fetch("http://localhost:9000/frontend/data/map")
//       .then(res => {
//         const item = res.json()
//         console.log(item)
//         return item})
//       .then(item => {
//         setData(item)})
//       .catch(error => {console.log(error)})
// }

// useEffect(()=>{
//   callAPI();
//   console.log('get request sent');
// },[])

function xScale(x){
  var len = left+(window.innerWidth/2-left)*(x/360)
  return len;
};
function yScale(y){
  var len = top+(window.innerHeight*3/4-top)*(y/240)
  return len;
};

var pts = []
positions.map((position)=>(
  pts.push(xScale(position.x), yScale(position.y))
))
console.log(pts);

export default function Map() {

    return (
      <Stage width={window.innerWidth/2} height={window.innerHeight*3/4}>
        <Layer>
            <Rect
              x = {left}
              y = {top}
              width={window.innerWidth/2-left}
              height={window.innerHeight*3/4-top}
              fill = 'grey'
              opacity = {0.3}
            />
            {aliens.map((alien)=> (
                <Circle
                x={xScale(alien.x)}
                y={yScale(alien.y)}
                radius={15}
                fill={alien.color}
                shadowBlur={5}
              />
               
            ))}
        
            {infras.map((infra)=> (
                    <Rect
                    x={xScale(infra.x)+left}
                    y={yScale(infra.y)+top}
                    width={15}
                    height={15}
                    fill= 'purple'
                    shadowBlur={5}
                />
                ))
                }
            {poles.map((pole)=> (
                    <Circle
                    x={xScale(pole.x)+left}
                    y={yScale(pole.y)+top}
                    radius={15}
                    fill= 'white'
                    stroke = 'black'
                    shadowBlur={5}
                />
                ))
                }
            
            <Line
            points = {pts}
            stroke = 'red'
            />
            <Circle
            x = {pts[pts.length -2]}
            y = {pts[pts.length -1]}
            radius = '3'
            fill = 'white'
            stroke = 'yellow'
            />
            
        </Layer>
      </Stage>
    );
  }