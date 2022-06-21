//draws the map, still going
import React from 'react';
import {Stage, Layer, Circle, Rect, Line, Image} from 'react-konva';

// roverCoordinate : {x:0, y:3},
// alienCoordinate : [{x:5, y:2, color:''}, {x:7, y:4, color: ''}],
// infraCoordinate : [{x:1, y:3}, {x:2, y:5}]

// first we need to create a stage

var aliens = [{x:50, y:20, color:'red'}, {x:70, y:40, color: 'blue'}]
var infras = [{x:100, y:30}, {x:20, y:50}]
var poles = [{x:200, y:10}, {x:40, y:60}]
var position = [{x:0,y:0},{x:5,y:0},{x:20,y:0},{x:30,y:0},{x:30,y:15}]

const left = 50;
const top = 100;
//const alienImage =  useImage('https://www.indiewire.com/wp-content/uploads/2021/06/Yoda.png');

export default function Map() {

    return (
      <Stage width={window.innerWidth/2} height={window.innerHeight*2/3}>
        <Layer>
            {aliens.map((alien)=> (
                <Circle
                x={alien.x+left}
                y={alien.y+top}
                width={25}
                height={25}
                fill={alien.color}
                shadowBlur={5}
                opacity={0.2}
              />
               
            ))}
            {aliens.map((alien)=>(
                <Circle
                x={alien.x+left}
                y={alien.y+top}
                width={5}
                height={5}
                fill={alien.color}
               />
            ))}
        
            {infras.map((infra)=> (
                    <Rect
                    x={infra.x+left}
                    y={infra.y+top}
                    width={15}
                    height={15}
                    fill= 'purple'
                    shadowBlur={5}
                />
                ))
                }
            {poles.map((pole)=> (
                    <circle
                    x={pole.x+left}
                    y={pole.y+top}
                    width={15}
                    height={15}
                    fill= 'black'
                    shadowBlur={5}
                />
                ))
                }
        </Layer>
      </Stage>
    );
  }