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