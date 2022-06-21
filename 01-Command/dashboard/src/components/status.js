//aims to show miles, displacement, direction/turn
//similar to alien.js format
import '../App.css';
import React, {useState, useEffect} from 'react';

function Status(){

const [data, setData] = useState({});

  const callAPI = () =>{
    fetch("http://localhost:9000/frontend/data")
        .then(res => {
          const item = res.json()
          console.log(typeof item.alienCoordinate)
          console.log(item)
          return item})
        .then(res => {
          setData(res.alienCoordinate[0])})
        .catch(error => {console.log(error)})
  }
     
  useEffect(()=>{
    callAPI();
    console.log('get request sent');
  },[]) 

  return (
      <div className="App">
        <header className="App-header">
          <p className="App-intro">{'number of aliens discovered: '+data}</p>
          
        </header>
      </div>
    );
    //<p className="App-intro">{'number of underground infrastructure discovered: '+data.api.infraCoordinate.length}</p>
          

}

export default Status;