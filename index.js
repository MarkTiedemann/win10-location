'use strict'

const geolocation = require('./prebuilt/windows.devices.geolocation')
const locator = new geolocation.Geolocator()

module.exports = () => {
    return new Promise ((resolve, reject) => {
        locator.getGeopositionAsync((err, res) => {
            if (err) reject(err)
            else resolve({
                longitude: res.coordinate.longitude,
                latitude: res.coordinate.latitude
            })
        })
    })
}
