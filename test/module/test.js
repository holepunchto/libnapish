const assert = require('assert')

const addon = require(process.argv[2])

assert.strictEqual(addon, 'Hello from addon')
