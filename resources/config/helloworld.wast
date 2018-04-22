(module
 (type $v (func))
 (type $iv (func (param i32)))
 (import "Keto" "console" (func $../typescript_contract_sdk/assembly/index/Keto.console (param i32)))
 (global $HEAP_BASE i32 (i32.const 132))
 (memory $0 1)
 (data (i32.const 4) "\12\00\00\00[\00d\00e\00b\00i\00t\00]\00h\00e\00l\00l\00o\00 \00w\00o\00r\00l\00d\00")
 (data (i32.const 44) "\13\00\00\00[\00c\00r\00e\00d\00i\00t\00]\00h\00e\00l\00l\00o\00 \00w\00o\00r\00l\00d\00")
 (data (i32.const 88) "\14\00\00\00[\00p\00r\00o\00c\00e\00s\00s\00]\00h\00e\00l\00l\00o\00 \00w\00o\00r\00l\00d\00")
 (export "debit" (func $assembly/index/debit))
 (export "credit" (func $assembly/index/credit))
 (export "process" (func $assembly/index/process))
 (export "memory" (memory $0))
 (func $assembly/index/debit (; 1 ;) (type $v)
  ;;@ assembly/index.ts:5:7
  (call $../typescript_contract_sdk/assembly/index/Keto.console
   ;;@ assembly/index.ts:5:15
   (i32.const 4)
  )
 )
 (func $assembly/index/credit (; 2 ;) (type $v)
  ;;@ assembly/index.ts:8:7
  (call $../typescript_contract_sdk/assembly/index/Keto.console
   ;;@ assembly/index.ts:8:15
   (i32.const 44)
  )
 )
 (func $assembly/index/process (; 3 ;) (type $v)
  ;;@ assembly/index.ts:11:7
  (call $../typescript_contract_sdk/assembly/index/Keto.console
   ;;@ assembly/index.ts:11:15
   (i32.const 88)
  )
 )
)
