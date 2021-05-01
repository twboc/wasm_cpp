#include "WASMNode.hpp"

#include "WASMNode.constructor.cpp"
#include "WASMNode.native.cpp"

WASMNode& WASMNode::Noop()
{
    return *this;
}

WASMNode& WASMNode::ReadFile(FILE *file, const char* path, char* mode)
{
    file = std::fopen(path, mode);
    std::fseek(file, 0, SEEK_END);
    long length = std::ftell(file);
    uint8_t *bytes = static_cast<uint8_t *>(std::malloc(length));
    std::fseek(file, 0, SEEK_SET);
    std::fread(bytes, 1, length, file);
    std::fclose(file);
    SetFileNode(file, path, bytes, length);
    return *this;
}

WASMNode& WASMNode::Instantiate()
{
    wasmer_result_t instantiation_result = wasmer_instantiate(&native.instance, file_node.bytes, file_node.length, native.imports, 0);
    assert(instantiation_result == WASMER_OK);
    NativeSetInstanceExports();
    NativeSetExportsLen();
    NativeSetExportsNames();
    return *this;
}

WASMNode& WASMNode::SetFileNode(FILE *file, const char* path, uint8_t *bytes, long length)
{
    file_node.path = path;
    file_node.file = file;
    file_node.bytes = bytes;
    file_node.length = length;
    return *this;
}

WASMNode& WASMNode::Test01()
{
    wasmer_export_descriptor_t test;
    wasmer_byte_array export_descriptor_name = wasmer_export_descriptor_name(&test);
    return *this;
}
