// note that the compiled addon is placed under following path
var windowsFs = require('../build/Release/addon');
var fs = require('fs');

console.log(windowsFs.lstatSync('C:\\Windows'));

try {
  console.log(windowsFs.lstatSync('C:\\Windows2'));
} catch(Err) {
  console.log(Err);
}
