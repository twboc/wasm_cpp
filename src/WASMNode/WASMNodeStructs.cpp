#include "wasmer.h"
#include <vector>

struct WASMNode_file_node_t {
    const char* path;
    FILE *file;
    uint8_t *bytes;
    long length;
};

struct WASMNode_native_t {
    wasmer_instance_t *instance;
    wasmer_exports_t *exports;
    wasmer_import_t *imports;
    int exports_len;
    std::vector<char> exports_names;
};