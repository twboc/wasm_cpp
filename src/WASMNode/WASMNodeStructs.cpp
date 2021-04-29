#include "wasmer.h"
#include <iostream>
#include <assert.h>

struct WASMNode_file_node_t {
    const char* path;
    FILE *file;
    uint8_t *bytes;
    long length;
};