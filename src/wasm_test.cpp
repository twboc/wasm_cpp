#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <iostream>
#include "wasmer.h"

void TestWasmFile(const char* path, char* _mode = "r") {
    // Read the Wasm file bytes.
    FILE *file = std::fopen(path, "r");
    std::fseek(file, 0, SEEK_END);
    long len = std::ftell(file);
    uint8_t *bytes = static_cast<uint8_t *>(std::malloc(len));
    std::fseek(file, 0, SEEK_SET);
    std::fread(bytes, 1, len, file);
    std::fclose(file);

    // Prepare the imports.
    wasmer_import_t imports[] = {};
 
    // Instantiate!
    wasmer_instance_t *instance = NULL;
    wasmer_result_t instantiation_result = wasmer_instantiate(&instance, bytes, len, imports, 0);
 
    assert(instantiation_result == WASMER_OK);

    // Let's call a function.
    // Start by preparing the arguments.
 
    // Value of argument #1 is `7i32`.
    wasmer_value_t argument_one;
    argument_one.tag = WASM_I32;
    argument_one.value.I32 = 7;
 
    // Value of argument #2 is `8i32`.
    wasmer_value_t argument_two;
    argument_two.tag = WASM_I32;
    argument_two.value.I32 = 8;
 
    // Prepare the arguments.
    wasmer_value_t arguments[] = {argument_one, argument_two};
 
    // Prepare the return value.
    wasmer_value_t result_one;
    wasmer_value_t results[] = {result_one};
 
    // Call the `sum` function with the prepared arguments and the return value.
    wasmer_result_t call_result = wasmer_instance_call(instance, "add", arguments, 2, results, 1);
 
    // Let's display the result.
    printf("Call result:  %d\n", call_result);
    printf("Result: %d\n", results[0].value.I32);
 
    // `sum(7, 8) == 15`.
    assert(results[0].value.I32 == 15);
    assert(call_result == WASMER_OK);
 
    wasmer_instance_destroy(instance);

}