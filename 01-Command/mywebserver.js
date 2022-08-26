var express = require('express');
var server = express();
let htmlContent = ` 
<!DOCTYPE html> 
<html>
    <body>
        <h2>hello</h2>
    </body>
</html> 
`;
server.get('/', function(req, res) { 
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end(htmlContent); });
console.log('Server is running on port 3000'); server.listen(3000,'127.0.0.1');

