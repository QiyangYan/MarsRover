import React, {useEffect, useState} from 'react'; 
import fetch from 'node-fetch';

const FetchData = () =>{
    const [data, setData] = useState('');
    useEffect(()=>{
        const getInfo = ()=>{
            fetch('http://localhost:9000')
            .then(
                response  => {
                  console.log(response);
                },
               rejection => {
                  console.error(rejection.message);
               })
            .then(response => {
            console.log(response);
            setData(response);
            });
        }
        getInfo();
    }, [data])
    
    return(
    <div><h>info: {data}</h></div>
    )
    
}

export default FetchData;