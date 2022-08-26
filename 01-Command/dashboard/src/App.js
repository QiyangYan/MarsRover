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