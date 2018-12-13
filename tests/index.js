// note that the compiled addon is placed under following path
var windowsFs = require('../build/Release/addon');
var fs = require('fs');
var mkdirp = require('mkdirp');

console.log(windowsFs.lstatSync('C:\\Windows\\System32'));

try {
  console.log(windowsFs.lstatSync('C:\\Windows2'));
} catch(Err) {
  console.log(Err);
}

fs.mkdirSync('C:\\test ä');
console.log(windowsFs.lstatSync('C:\\test ä'));
fs.rmdirSync('C:\\test ä');

const path = 'C:\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar';
mkdirp(path, () => {
  console.log(windowsFs.lstatSync(path));
});

const path = 'C:\\foobar\\foobar';
mkdirp(path, () => {
  console.log(windowsFs.lstatSync("\\\\?\\"+path));
});
