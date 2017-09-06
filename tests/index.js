// note that the compiled addon is placed under following path
var test = require('../build/Release/addon');
var fs = require('fs');
// `Hello` function returns a string, so we have to console.log it!
console.log(test.statSync('C:\\Windows'));
console.log(fs.statSync('C:\\Windows'));
