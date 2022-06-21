# Mars_Bar__EE2_Final_Project__
EE2_Group8_Summer_Final_Project

Command – Christina  

Control – Andy  

Drive – Nick  

Vision – Charli  

Energy – Yuqi, Jack 

Radar – Roy  

mars picture: https://mars.nasa.gov/system/news_items/main_images/8944_1-PIA24546-1280.jpg 
alien picture:https://www.indiewire.com/wp-content/uploads/2021/06/Yoda.png

JSON format:
- updates every 0.1s
- speed and distance all in real distance in cm, cm/s
- 

from esp to webserver:
{
    speed: 2, //float
    distanceExplored: 3, //float
    displacementFromBase: 3, //float
    roverCoordinate: (0,3) //coordinate
    alienCoordinate: [(2,5), (1,3)], // list of coordinates
    infraCoordinate: [(2,5), (1,3)], // list of coordinates
    batteryLevel: 1, //int from 0-3, needs experiments on relationship between battery and distance
    return: false //boolean, depends on displacement and battery level
}

from webserver to esp:
{   
    mode: '', //'auto' or 'manual'
    command: '' //'returnToBase', 'forward', 'backward', 'left', 'right', 'stop' (?speed control)
}

360*240cm
