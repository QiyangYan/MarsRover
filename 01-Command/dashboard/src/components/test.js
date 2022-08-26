
import React, {useState, useEffect} from 'react';
import {Stage, Layer, Circle, Rect, Line, Text} from 'react-konva';

export default function test(){
    
  var testdata =[{x_axis: 20, y_axis: 20, color:'', ball_x: '', ball_y: ''},
  {x_axis: 40, y_axis: 20, color:'R', ball_x: '50', ball_y: '20'},
  {x_axis: 20, y_axis: 20, color:'R', ball_x: '50', ball_y: '20'},
  {x_axis: 20, y_axis: 40, color:'G', ball_x: '0', ball_y: '20'},
  {x_axis: 20, y_axis: 60, color:'G', ball_x: '0', ball_y: '20'}]
  var positionBuffer = [];
  var tmp = [];

  const drawLine = (arr) =>{
    <Line
      points = {arr}
      stroke = 'red'
      closed = {false}
    />
  }

  const drawPath = () =>{
    testdata.map((line)=> {
      console.log('line: '+line)
      tmp = [line.x_axis,line.y_axis];
      tmp.push(positionBuffer)
      console.log('tmp: '+tmp)
        drawLine(tmp);
        positionBuffer=line;
    }  
    )
  }

  return(<div>{drawPath}</div>)
}
