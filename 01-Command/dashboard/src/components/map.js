//working map without database
import React, {useState, useEffect} from 'react';
import {Stage, Layer, Circle, Rect, Line, Text} from 'react-konva';


const left = 50;
const top = 50;
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
  var len = window.innerHeight*3/4-50-(window.innerHeight*3/4-50-top)*(y/240)
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
  else{return '';}
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
      var info = data.filter((item, index, self) => 
      index === self. findIndex((t) => (
          t.x_axis === item.x_axis && t.y_axis === item.y_axis 
          && t.ball_x === item.ball_x && t.ball_y === item.ball_y && t.color ===item.color
      )))
    setData(info);
      console.log('get request sent');
    }, 1000);
    return () => clearInterval(interval);
  },[])

  data.map((line)=>(
    pts.push(xScale(line.x_axis), yScale(line.y_axis))
  ))
  console.log('path: '+ pts);

  const drawLine = (pts) =>{
    for(let i=0; i<pts.length-4;i = i+2){
      console.log(pts.slice(i, i+4));
      <Line
            points = {pts.slice(i, i+4)}
            stroke = 'red'
            closed = {false}
            />
    }
  }

    return (
      <Stage width={window.innerWidth/2} height={window.innerHeight-top}>
        <Layer>
            <Rect
              x = {left}
              y = {top}
              width={window.innerWidth/2-left}
              height={window.innerHeight*3/4-top-50}
              fill = 'white'
              opacity = {0.6}
            />
            {data.map((line)=> (
                <Circle
                x={xScale(line.ball_x)}
                y={yScale(line.ball_y)}
                radius={10}
                fill={color_decode(line.color)}
                shadowBlur={5}
              />
            ))}
            {data.map((line)=> (
                <Text
                x={xScale(line.ball_x)}
                y={yScale(line.ball_y)+10}
                text = {'('+line.ball_x+', '+line.ball_y+')'}
                fontFamily = 'Courier New'
                fill = 'black'
                fontSize= {15}
                />
            ))}

            <Line
            points = {pts}
            stroke = 'red'
            closed = {false}
            />

            <Circle
            x = {pts[pts.length -2]}
            y = {pts[pts.length -1]}
            radius = {3}
            fill = 'white'
            stroke = 'yellow'
            />
            
        </Layer>
        <Layer>
          <Text
            text = 'alien' 
            x = {left}
            y = {window.innerHeight*3/4}
            fontFamily = 'Courier New'
            fill = 'white'
            fontSize= {24}
          />
          <Circle
                x={left + 100}
                y={window.innerHeight*3/4 +10}
                radius={10}
                fill='red'
                shadowBlur={5}
          />
          <Circle
                x={left + 140}
                y={window.innerHeight*3/4+10}
                radius={10}
                fill="yellow"
                shadowBlur={5}
          />
          <Circle
                x={left + 180}
                y={window.innerHeight*3/4+10}
                radius={10}
                fill='blue'
                shadowBlur={5}
          />
          <Circle
                x={left + 220}
                y={window.innerHeight*3/4+10}
                radius={10}
                fill='green'
                shadowBlur={5}
          />
          <Circle
                x={left + 260}
                y={window.innerHeight*3/4+10}
                radius={10}
                fill='darkgreen'
                shadowBlur={5}
          />
          <Circle
                x={left + 300}
                y={window.innerHeight*3/4+10}
                radius={10}
                fill='magenta'
                shadowBlur={5}
          />
          <Text
            text = 'tower' 
            x = {left}
            y = {window.innerHeight*3/4+30}
            fontFamily = 'Courier New'
            fill = 'white'
            fontSize= {24}
          />
          <Circle
                x={left + 100}
                y={window.innerHeight*3/4 +40}
                radius={10}
                fill='white'
                shadowBlur={5}
          />
          <Text
            text = 'infrastructure' 
            x = {left}
            y = {window.innerHeight*3/4+60}
            fontFamily = 'Courier New'
            fill = 'white'
            fontSize= {24}
          />
          <Rect
            x={left + 220}
            y={window.innerHeight*3/4 +62}
            width={20}
            height={20}
            fill='purple'
            shadowBlur={5}
          />
          
        </Layer>
      </Stage>
      
      
    );
  }
  