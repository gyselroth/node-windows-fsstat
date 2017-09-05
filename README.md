# node-windows-fsstat

Alternative fs.statSync(path) for windows based systems. Since Windows does not have inodes and the node fs module
provides only inodes which are somehow converted numbers from Windows fileId into a posix like inode.
But this conversion can cause inode conflicts, see https://github.com/nodejs/node/issues/12115.

This module provides statSync(path) and includes the truly unique fileId from Windows besides other stat attributes.

## Usage

```javascript
var windowsFs = require('windows-fsstat');
console.log(windowsFs.statSync('C:\\windows'));

{ fileId: 562949953560707,
  size: 0,
  atime: 2017-09-05T08:53:42.000Z,
  mtime: 2017-09-05T08:53:42.000Z,
  ctime: 2015-12-08T08:15:42.000Z,
  directory: true }
````
