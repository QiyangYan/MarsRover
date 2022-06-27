import '../App.css';
import React, {useState, useEffect} from 'react';
import {Stage, Layer, Rect, Text} from 'react-konva';

function Status(){

  const [data, setData] = useState({});

  const direction = data.direction;
  const distance = data.distance;

  // const callAPI = () =>{
  //   fetch("http://localhost:9000/frontend/data")
  //       .then(res => {
  //         const item = res.json()
  //         return item})
  //       .then(item => {
  //         setData(item)})
  //       .catch(error => {console.log(error)})
  // }
     
  // useEffect(()=>{
  //   const interval = setInterval(() => {
  //     callAPI();
  //     console.log('status get request sent');
  //   }, 1000);
  //   return () => clearInterval(interval);
  // },[])

  return ( 
      <div>
        <h1 className="App-text"> 
          rover direction: {direction} <br></br>
          distance travelled: {distance}
        </h1>
          
      </div>
    );
      

}


export default Status;