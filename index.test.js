const audio = require('./index')

test('list devices', () => {
    const devices = audio.listDevices()
    expect(devices.length).toBeGreaterThan(1)
    expect(devices[0].getName()).toBeDefined()
    expect(devices[0].mute()).toBeTruthy()
    expect(devices[0].unmute()).toBeTruthy()

});

test('default device', () => {
    const device = audio.defaultDevice()
    expect(device).toBeDefined()
    expect(device.getName()).toBeDefined()
    expect(device.mute()).toBeTruthy()
    expect(device.unmute()).toBeTruthy()
});


test('get name', () => {
    const device = audio.defaultDevice()
    const name = device.getName()
    expect(device.getName()).toBe(name)
});