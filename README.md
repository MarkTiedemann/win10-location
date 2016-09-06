
# win10-location

**Windows 10 Geolocation API simplified, promisified, and prebuilt with [NodeRT](https://github.com/NodeRT/NodeRT).**

## Installation

```
npm install win10-location
```

## Quickstart

```js

const location = require('win10-location')

location()
    .then(console.log)
    // => { longitude: 10.921161, latitude: 35.605253 }

```

## Development

- [**Prerequesites**](https://github.com/NodeRT/NodeRT#nodert-prerequisites)
- **Building:** Open Powershell as an administrator and run: `.\build.ps1`

## License

[WTFPL](http://www.wtfpl.net/) – Do What the F*ck You Want to Public License.

Made with :heart: by [@MarkTiedemann](https://twitter.com/MarkTiedemannDE).
