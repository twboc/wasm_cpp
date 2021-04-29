// The entry file of your WebAssembly module.

export function add(a: i32, b: i32): i32 {
  return a + b;
}


export function crazyAdd(a: i32, b: i32): i32 {
  return a + b + 1000;
}