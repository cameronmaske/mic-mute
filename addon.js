const addon = require('bindings')('addon');

// var obj = new addon.MyObject(10);
// console.log(obj.plusOne()); // 11
// console.log(obj.plusOne()); // 12
// console.log(obj.plusOne()); // 13

// console.log(obj.multiply().value()); // 13
// console.log(obj.multiply(10).value()); // 130

// var newobj = obj.multiply(-1);
// console.log(newobj.value()); // -13
// console.log(obj === newobj); // false

try {
    const d = addon.defaultDevice()
    console.log(d)

} catch (error) {
    console.log("erere")
    console.log(error)
}

// const devices = addon.listDevices(2)
// console.log(devices)

/*
const devices = addon.listDevices()

const device = devices[0]
device.isDefault
device.name
device.mute()
device.unmute()
*/