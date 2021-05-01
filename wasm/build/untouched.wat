(module
 (type $i32_=>_i32 (func (param i32) (result i32)))
 (type $i32_i32_=>_i32 (func (param i32 i32) (result i32)))
 (type $i32_i32_i32_=>_i32 (func (param i32 i32 i32) (result i32)))
 (global $~lib/memory/__data_end i32 (i32.const 8))
 (global $~lib/memory/__stack_pointer (mut i32) (i32.const 16392))
 (global $~lib/memory/__heap_base i32 (i32.const 16392))
 (memory $0 0)
 (table $0 1 funcref)
 (export "crazyAdd" (func $assembly/index/crazyAdd))
 (export "add" (func $assembly/index/add))
 (export "add2" (func $assembly/index/add2))
 (export "memory" (memory $0))
 (func $assembly/index/crazyAdd (param $0 i32) (param $1 i32) (param $2 i32) (result i32)
  local.get $0
  local.get $1
  i32.add
  local.get $2
  i32.add
  i32.const 1000
  i32.add
 )
 (func $assembly/index/add (param $0 i32) (param $1 i32) (result i32)
  local.get $0
  local.get $1
  i32.add
 )
 (func $assembly/index/add2 (param $0 i32) (result i32)
  local.get $0
  i32.const 2
  i32.add
 )
)
