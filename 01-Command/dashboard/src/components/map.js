//working map without database
import React, {useState, useEffect} from 'react';
import {Stage, Layer, Circle, Rect, Line} from 'react-konva';


const left = 50;
const top = 100;
//var espInfo = [{x_axis: 1, y_axis: 0, color:'', ball_x: '', ball_y: ''}];


//const alienImage =  useImage('https://www.indiewire.com/wp-content/uploads/2021/06/Yoda.png');

// const callAPI = () =>{
//   fetch("http://localhost:9000/frontend/data/alien")
//       .then(res => {
//         const item = res.json()
//         console.log('alieninfo: '+item)
//         return item})
//       .then(item => {if(alien[-1]!==item){
//         setAlien((prev)=>[...prev,item])}}
//         )
//       .then(console.log(alien.alien_x+alien.alien_y+alien.alien_color))
//       .catch(error => {console.log('alienerror: '+error)})

//   fetch("http://localhost:9000/frontend/data/path")
//   .then(res => {
//     const item = res.json()
//     console.log('pathinfo: '+ item)
//     return item})
//   .then(item => {if(path[-1]!==item){
//       setPath((prev)=>[...prev,item])}}
//       )
//   .then(console.log(path.x_axis+path.y_axis))
//   .catch(error => {console.log('patherror: '+error)})
// }




function xScale(x){
  var len = left+(window.innerWidth/2-left)*(x/360)
  return len;
};
function yScale(y){
  var len = top+(window.innerHeight*3/4-top)*(y/240)
  return len;
};
function color_decode(color){
  if (color === 'R'){
    return 'red';
  }
  else if(color === 'Y'){
    return 'yellow';
  }
  else if(color === 'B'){
    return 'blue';
  }
  else if(color === 'G'){
    return 'green';
  }
  else if(color === 'D'){
    return 'darkgreen';
  }
  else if(color === 'P'){
    return 'magenta';
  }
  else if(color === 'W'){
    return 'white';
  }
  else{return 'black';}
}

var pts = []

export default function Map() {
  const [data, setData] = useState([{x_axis: 0, y_axis: 0, color:'', ball_x: '', ball_y: ''}]);
  
  const callAPI = () =>{
    fetch("http://18.212.255.51:9000/frontend/data")
      .then(res => {
        const item = res.json();
        console.log('callAPI: '+ item);
        return item;})
      .then((item)=>{setData(item)})
      .catch(error => {console.log(error)})
  }

  useEffect(()=>{
    const interval = setInterval(() => {
      callAPI();
      console.log('get request sent');
    }, 500);
    return () => clearInterval(interval);
  },[])
  console.log('aftereffectdata: '+data[0].x_axis);
  data.map((line)=>(
    pts.push(xScale(line.x_axis), yScale(line.y_axis))
  ))
  console.log('path: '+ pts);



    return (
      <Stage width={window.innerWidth/2} height={window.innerHeight*3/4}>
        <Layer>
            <Rect
              x = {left}
              y = {top}
              width={window.innerWidth/2-left}
              height={window.innerHeight*3/4-top}
              fill = 'white'
              opacity = {0.5}
            />
            {data.map((line)=> (
                <Circle
                x={xScale(line.ball_x)}
                y={yScale(line.ball_x)}
                radius={10}
                fill={color_decode(line.color)}
                shadowBlur={5}
              />
               
            ))}
            
            <Line
            points = {pts}
            stroke = 'red'
            />
            <Circle
            x = {pts[pts.length -2]}
            y = {pts[pts.length -1]}
            radius = {3}
            fill = 'white'
            stroke = 'yellow'
            />
            
        </Layer>
      </Stage>
    );
  }
  