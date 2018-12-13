var windowsFs = require('../build/Release/addon');
var fs = require('fs');
var mkdirp = require('mkdirp');

describe('lstat', () => {
  it('lstatSync on c:\\Windows\\System32', () => {
    var result = windowsFs.lstatSync('C:\\Windows\\System32');
    expect(result.directory).toBe(true);
    expect(result.size).toBe(0);
  });

  it('lstatSync not existing folder', () => {
    expect(() => {
      windowsFs.lstatSync('C:\\Windows2');
    }).toThrow();
  });

  it('lstatSync on file C:\\Windows\\win.ini', () => {
    var result = windowsFs.lstatSync('C:\\Windows\\win.ini');
    expect(result.directory).toBe(false);
    expect(result.size > 0).toBe(true);
  });

  it('lstatSync non ascii character in path', () => {
    fs.mkdirSync('C:\\test ä');
    var result = windowsFs.lstatSync('C:\\test ä');
    expect(result.directory).toBe(true);
    expect(result.size).toBe(0);
    fs.rmdirSync('C:\\test ä');
  });

  it('lstatSync path > MAX_PATH', () => {
    var path = 'C:\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar\\foobar';
    mkdirp(path, () => {
      var result = windowsFs.lstatSync(path);
      expect(result.directory).toBe(true);
      expect(result.size).toBe(0);
    });
  });

  it('lstatSync path using \\\\?\\ prefix', () => {
    var path = 'C:\\foobar\\foobar';
    mkdirp(path, () => {
      var result = windowsFs.lstatSync("\\\\?\\"+path);
      expect(result.directory).toBe(true);
      expect(result.size).toBe(0);
    });
  });
});
