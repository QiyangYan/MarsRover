//the frontend toplevel file

import './App.css';
//import axios from 'axios';
// import Status from './components/status';
//import Battery from './components/battery';
import React from 'react'
import Command from './components/command';
import Map from './components/map';


function App() {
  return(
    <div className="App">
      <header className="App-header"> 
        Mars Rover
      </header>
      <Map/ >
      <Command/ >
      
    </div>
  )
}

export default App;

  // const [data, setData] = useState({apiResponse: ''});

  // const callAPI = () =>{
  //   fetch("http://localhost:9000/frontend/data")
  //       .then(res => res.text())
  //       .then(res => {setData({apiResponse: res})})
  //       .catch(error => {console.log(error)})
  // }
     
  // useEffect(()=>{
  //   callAPI();
  //   console.log('get request sent');
  // },[]) 

  // const sendData = () =>{
  //   fetch("http://localhost:9000/frontend/post",{
  //     method: 'POST',
  //     body: JSON.stringify({msg: 'Hi, I am the web client!', dt: data.apiResponse}),
  //     headers: {'Content-Type': 'application/json;charset=utf-8'}
  //   })
  //     .then(res => res.text())
  //     .catch(error => {console.log(error)})
  // }  
  
  // useEffect(()=>{
  //   sendData();
  //   console.log('data sent');
  // },[])
  







/*
//const data = JSON.parse(data);

var data;

const fetchData = async() => {
  try{
    var res = await axios.get('http://localhost:3100/');
    console.log(res);
    data=res.text;
  } catch(error){
    console.log(error);
  }
}

// const sendData = async() =>{
//   axios.post('http://localhost:3100/post',{
//     str1: 'string 1',
//   });
//   console.log('post request sent');
// }




// function fetchData(){
//   fetch('http://localhost:3100/',{
//     method: 'GET',
//     body: 
//     header:
//   }
//   )
// }


function App(){
  

  return (
    <div className='app'>
      <h1>Web</h1>
      <body>
        <p>
          Hello
          {data}
          
        </p>
      </body>
    </div>
  );
}

export default App;

/*import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

export default App;
*/

