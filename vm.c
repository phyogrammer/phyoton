#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

// Global static VM instance, not really a good choice if VM is designed to be
// embedded in other host applications. Better to pass explicitly take a VM
// pointer and pass it around so that host app can control when and where
// memory for the VM is allocted, run multiple VMs in parallel, etc.
// Maybe change is later? I don't know, I'm not smart enough yet
VM vm;

void initVM()
{
}

void freeVM()
{
}

static InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
        dissambleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN:
            {
                return INTERPRET_OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk *chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
