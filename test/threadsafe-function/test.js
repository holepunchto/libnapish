const assert = require('assert')

const addon = require(process.argv[2])

const events = []

addon((event, matches) => events.push([event, matches]))

process.on('exit', () => {
  assert.deepStrictEqual(events, [
    ['context', true],
    ['call', true],
    ['finalize', true]
  ])
})
