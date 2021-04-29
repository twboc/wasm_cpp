#ifndef WASMNODE_H
#define WASMNODE_H
#pragma once

#include "wasmer.h"
#include <iostream>
#include <assert.h>

#include "./WASMNodeStructs.cpp"
	
class WASMNode  
{
	private:
		FILE file;
		WASMNode_file_node_t file_node;
		wasmer_import_t imports;
		wasmer_instance_t *instance = NULL;
		WASMNode& SetFileNode(FILE *file, const char* path, uint8_t *bytes, long length);

	public:

		WASMNode(const char* path, char* _mode = "r");
		~WASMNode();

		WASMNode& Noop();
		WASMNode& ReadFile(FILE *file, const char* path, char* _mode = "r");
		WASMNode& Instantiate();

};
#endif