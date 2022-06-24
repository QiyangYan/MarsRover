//this gets information for the map, working, will put the following in the map function

import '../App.css';
import React, {useState, useEffect} from 'react';

function Map(){

  const [data, setData] = useState({});

  const aliens = data.alienCoordinate;
  const infras = data.infraCoordinate;
  const towers = data.tower;
  const rover = data.roverCoordinate;

  const callAPI = () =>{
    fetch("http://localhost:9000/frontend/data")
        .then(res => {
          const item = res.json()
          console.log(item)
          return item})
        .then(item => {
          setData(item)})
        .catch(error => {console.log(error)})
  }
     
  useEffect(()=>{
    callAPI();
    console.log('get request sent');
    console.log(aliens);
    console.log(infras);
    console.log(rover);
    console.log(tower);
  },[])

  return ( 
      <div className="App">
        <header className="App-header"> 
          {aliens.map((alien)=> (<p className="App-intro">{alien.x}</p>))}
        </header>
          
      </div>
    );
      

}


export default Map;