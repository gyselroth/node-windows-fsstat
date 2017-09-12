# node-windows-fsstat

[![Build status](https://ci.appveyor.com/api/projects/status/iikdg1nngoc1272j?svg=true)](https://ci.appveyor.com/project/raffis/node-windows-fsstat)
[![npm](https://img.shields.io/npm/v/@gyselroth/windows-fsstat.svg)](https://www.npmjs.com/package/@gyselroth/windows-fsstat)
[![GitHub release](https://img.shields.io/github/release/gyselroth/node-windows-fsstat.svg)](https://github.com/gyselroth/node-windows-fsstat/releases)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/gyselroth/windows-fsstat/master/LICENSE)

Alternative fs.lstatSync(path) for windows based systems. Since Windows does not have inodes and the node fs module
provides only an inode property which is a converted integer from the 64bit fileId (Windows equal to posix inode) integer.
But commonly known javascript can not handle 64bit integer, therefore the conversion into an integer can cause inode collisions
which can be fatal.
There is absolutely no reason that inode must be an integer. An inode or fileId is just an identifier and can be anything. Therefore
this module provides besides the attribute "ino" an attribute called "fileid" which is a HEX representation (string) of the windows fileId.

See node issue [#12115](https://github.com/nodejs/node/issues/12115) for further information.

## Install
```
npm install --save @gyselroth/windows-fsstat
```

## Usage

```javascript
var windowsFs = require('@gyselroth/windows-fsstat');
console.log(windowsFs.lstatSync('C:\\windows'));

{ fileid: '0x00020000000070FD',
  ino: 562949953450237,
  size: 0,
  atime: 2017-08-07T06:58:53.000Z,
  mtime: 2017-08-07T06:58:53.000Z,
  ctime: 2017-03-18T11:40:20.000Z,
  directory: true,
  symbolicLink: false }
````
