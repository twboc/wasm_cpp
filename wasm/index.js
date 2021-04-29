const wasmModule = require('./wasm')


for (var i = 0; i < 30; i++) {
    console.log(`wasmModule.add(${i}, ${i*2}) => `, wasmModule.add(i, i*2))
}
