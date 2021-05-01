#ifndef WASMNODE_H
#define WASMNODE_H
#pragma once

#include <iostream>
#include <vector>
#include <assert.h>

#include "wasmer.h"

#include "./WASMNode.structs.cpp"
#include "./WASMNode.utils.cpp"

class WASMNode  
{
	private:
		FILE file;
		WASMNode_native_t native;
		WASMNode_file_node_t file_node;

		WASMNode& SetFileNode(FILE *file, const char* path, uint8_t *bytes, long length);


		//Native wasmer methods
		WASMNode& NativeSetInstanceExports();
		WASMNode& NativeSetExportsLen();

		wasmer_export_t* NativeGetExportByIndex(int index);
		wasmer_import_export_kind NativeGetExportKind(wasmer_export_t* wasmer_export);
		wasmer_byte_array NativeGetExportName(wasmer_export_t* wasmer_export);
		const char*  NativeGetExportNameChar(wasmer_export_t* wasmer_export);
		void NativeSetExportsNames();
		WASMNode_native_t* NativeSetExportsKindNames(wasmer_export_t* wasmer_export, const char name);

	public:

		WASMNode(const char* path, char* mode = "r");
		~WASMNode();

		WASMNode& Noop();
		WASMNode& ReadFile(FILE *file, const char* path, char* mode = "r");
		WASMNode& Instantiate();

};
#endif