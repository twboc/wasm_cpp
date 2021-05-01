#include "WASMNode.hpp"

WASMNode::WASMNode(const char* path, char* mode)
{
    native.instance = NULL;
    native.exports = NULL;
    native.imports = {};
    native.exports_len = 0;
	ReadFile(&this->file, path, mode);
    Instantiate();
}
	
WASMNode::~WASMNode()
{
	wasmer_instance_destroy(native.instance);
    wasmer_exports_destroy(native.exports);
}

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

WASMNode& WASMNode::NativeSetInstanceExports()
{
    wasmer_instance_exports(native.instance, &native.exports);
}

WASMNode& WASMNode::NativeSetExportsLen()
{
    native.exports_len = wasmer_exports_len(native.exports);
    printf("Number of exports: %d\n", native.exports_len);
    return *this;
}

wasmer_export_t* WASMNode::NativeGetExportByIndex(int index)
{
    return wasmer_exports_get(native.exports, index);
};

wasmer_import_export_kind WASMNode::NativeGetExportKind(wasmer_export_t* wasmer_export)
{
    return wasmer_export_kind(wasmer_export);
};

wasmer_byte_array WASMNode::NativeGetExportName(wasmer_export_t* wasmer_export)
{
    return wasmer_export_name(wasmer_export);
};

const char* WASMNode::NativeGetExportNameChar(wasmer_export_t* wasmer_export)
{
    return wasmer_byte_array_to_string(
        wasmer_export_name(wasmer_export)
    );
};

void WASMNode::NativeSetExportsNames()
{
    for (int i = 0; i < native.exports_len; i++) 
    {
        wasmer_export_t* wasmer_export = NativeGetExportByIndex(i);
        const char* export_name = NativeGetExportNameChar(wasmer_export);
        printf("Export: %d  %s\n", native.exports_names.size(), export_name);
        native.exports_names.push_back(*export_name);
    }

};

///////////////////////////////////

WASMNode& WASMNode::Test01()
{
    wasmer_export_descriptor_t test;
    wasmer_byte_array export_descriptor_name = wasmer_export_descriptor_name(&test);
    return *this;
}
