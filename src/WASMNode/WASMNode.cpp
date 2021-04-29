#include "WASMNode.hpp"
	
WASMNode::WASMNode(const char* path, char* _mode)
{
    this->imports = {};
	this->ReadFile(&this->file, path, _mode);
    this->Instantiate();
}
	
WASMNode::~WASMNode()
{
	wasmer_instance_destroy(this->instance);
}

WASMNode& WASMNode::Noop()
{
    return *this;
}

WASMNode& WASMNode::ReadFile(FILE *file, const char* path, char* _mode)
{
    file = std::fopen(path, _mode);
    std::fseek(file, 0, SEEK_END);
    long length = std::ftell(file);
    uint8_t *bytes = static_cast<uint8_t *>(std::malloc(length));
    std::fseek(file, 0, SEEK_SET);
    std::fread(bytes, 1, length, file);
    std::fclose(file);
    this->SetFileNode(file, path, bytes, length);
    return *this;
}

WASMNode& WASMNode::Instantiate()
{
    wasmer_result_t instantiation_result = wasmer_instantiate(&instance, this->file_node.bytes, this->file_node.length, &this->imports, 0);
    assert(instantiation_result == WASMER_OK);
    return *this;
}

WASMNode& WASMNode::SetFileNode(FILE *file, const char* path, uint8_t *bytes, long length)
{
    this->file_node.path = path;
    this->file_node.file = file;
    this->file_node.bytes = bytes;
    this->file_node.length = length;
    return *this;
}
