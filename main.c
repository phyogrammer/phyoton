#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[])
{
    initVM();

    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 6.7);
    writeChunk(&chunk, OP_CONSTANT, 420);
    writeChunk(&chunk, constant,  420);
    
    writeChunk(&chunk, OP_RETURN, 420);

    disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    return 0;
}