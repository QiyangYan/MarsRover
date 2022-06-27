//the frontend toplevel file

import './App.css';
import React from 'react'
import Command from './components/command';
import Map from './components/map';
import Status from './components/status';
import {Grid, Paper} from "@mui/material";


function App() {
  return(
    <div className="App">
      <Grid container spacing={0} columns={12}>

        <Grid item xs={12}>
          <div>
            <header className="App-header"> 
              Mars Rover
            </header>
          </div>
        </Grid>
        
        <Grid item xs={7}>
          <Map/ >
        </Grid>
        <Grid item xs={4} spacing = {0} container direction='column'>
          <Grid item xs={1}/ >
          <Paper sx={{backgroundColor: 'white' , opacity: 0.7}}>
            <Status/ >
          </Paper>
          <Grid item xs={1}/ >
          <Paper sx={{backgroundColor: 'white' , opacity: 0.7}}>
            <Command/ >
          </Paper>
        </Grid>
        
        

      </Grid>
    </div>
    
    
    
  )
}

export default App;
{/* <Grid container spacing={2} columns={16}>
      <Grid item xs={8}>
        
          
        
      </Grid>
      <Grid item xs={8}>
        
      </Grid>
    </Grid> */}

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

