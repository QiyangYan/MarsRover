//this provides command to the rover, working

import React, {useState, useEffect} from 'react';

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
            <button onClick={setAuto}>AUTO</button> <br></br>
            <button onClick={setManual}>MANUAL</button> <br></br>
            <button onClick={forward}>FORWARD</button> <br></br>
            <button onClick={left}>LEFT</button>
            <button onClick={right}>RIGHT</button> <br></br>
            <button onClick={back}>BACK</button> <br></br>
            <button onClick={stop}>STOP</button>  
        </div>
    );
}

export default Command;

