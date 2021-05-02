#include <string>
#include "wasmer.h"

const char * wasmer_byte_array_to_string(wasmer_byte_array bytes) {
    char* temp = reinterpret_cast<char*>(const_cast<uint8_t*>(bytes.bytes));
    std::string str(temp, bytes.bytes_len);
    return str.c_str();
}