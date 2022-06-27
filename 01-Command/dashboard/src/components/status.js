import '../App.css';
import React, {useState, useEffect} from 'react';

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
        <h1 className="App-text status"> 
          Rover Direction: {direction} 
        </h1>
        <h1 className="App-text status">
          <br></br>
          Distance Travelled: {distance} cm
        </h1>
          
      </div>
    );
      

}


export default Status;