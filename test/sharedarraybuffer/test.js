const assert = require('assert')

const addon = require(process.argv[2])

assert.ok(addon.sharedArrayBuffer instanceof SharedArrayBuffer)
assert.strictEqual(addon.isSharedArrayBuffer, true)
assert.strictEqual(addon.hasSameData, true)
assert.strictEqual(addon.byteLength, 8)
assert.strictEqual(new Uint8Array(addon.sharedArrayBuffer)[0], 42)
