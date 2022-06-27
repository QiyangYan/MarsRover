//this provides command to the rover, working

import React, {useState, useEffect} from 'react';
import '../App.css';
import { Grid } from '@mui/material';

function Command(){
    const [mode, setMode] = useState('');
    // const toggleMode = () =>{
    //     if(mode === 'auto'){
    //         setMode('manual');
    //     }
    //     else{
    //         setMode('auto');
    //     }
    // };
    const setManual = () =>{
        setMode('manual');
    }
    const setAuto = () =>{
        setMode('auto');
    }

    const [command, setCommand] = useState('');
    const forward = () => {
        setCommand('forward');
    }
    const left = () => {
        setCommand('left');
    }
    const right = () => {
        setCommand('right');
    }
    const back = () => {
        setCommand('backward');
    }
    const stop = () => {
        setCommand('stop');
    }


    const sendData = () =>{
        fetch("http://18.212.255.51:9000/frontend/post",{
            method: 'POST',
            body: JSON.stringify({mode: mode, command: command}),
            headers: {'Content-Type': 'application/json;charset=utf-8'},
            })
            .then(res => res.text())
            .catch(error => {console.log(error)})
    }

    useEffect(()=>{
        sendData();
    }) 

    return(
        <div>
            <br></br>
            <Grid container spacing={0} columns={12}>
                <Grid item xs={6}>
                    <button className = 'button' onClick={setAuto}>AUTO</button>
                </Grid>
                <Grid item xs={6}>
                    <button className = 'button' onClick={setManual}>MANUAL</button>
                </Grid>
            </Grid>
             <br></br>
             <br></br>
            <button className = "button-arrow forward" onClick={forward}></button> <br></br><br></br>
            <Grid container spacing={0} columns={12}>
                <Grid item xs={2}></Grid>
                <Grid item xs={4}>
                    <button className = "button-arrow left" onClick={left}></button>
                </Grid>
                <Grid item xs={4}>
                    <button className = "button-arrow right" onClick={right}></button>
                </Grid>
            </Grid>
            <br></br>
            <button className = "button-arrow back" onClick={back}></button> <br></br>
            <br></br>
            <br></br>
            <button className = 'button' onClick={stop}>STOP</button>  
            <br></br>
            <h1 className='App-text mode'> Mode: {mode} </h1>
            <h1 className='App-text mode'> Current Command: {command} </h1>
        </div>
    );
}

export default Command;

