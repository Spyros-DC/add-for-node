var express = require('express');
var app = express();
var searchAddOn = require("./node_addon/build/Release/booksfinder.node");
app.use(express.static(__dirname + '/public'));        
var bodyParser = require('body-parser');
 
// create application/x-www-form-urlencoded parser 
var urlencodedParser = bodyParser.urlencoded({ extended: false })
var port = process.env.OPENSHIFT_NODEJS_PORT;
var ipaddress = process.env.OPENSHIFT_NODEJS_IP;
app.get('/', function(req, res){
    res.render();
});

app.post('/', urlencodedParser, function(req, res){
    res.json(searchAddOn.searchtitle(req.body.query));
});

app.listen(port, ipaddress, function(){
    console.log('listening on port: ' + port10);
});
