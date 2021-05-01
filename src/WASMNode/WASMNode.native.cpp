#include "WASMNode.hpp"

WASMNode& WASMNode::NativeSetInstanceExports()
{
    wasmer_instance_exports(native.instance, &native.exports);
}

WASMNode& WASMNode::NativeSetExportsLen()
{
    native.exports_len = wasmer_exports_len(native.exports);
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
        native.exports_names.push_back(*export_name);
    }
};
