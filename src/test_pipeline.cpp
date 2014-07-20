#include <sstream>
#include "tbb/pipeline.h"
#include "context.hh"
#include "instruction_fetch.hh"
#include "instruction_decode.hh"
#include "execution.hh"
#include "memory_stage.hh"
#include "write_back.hh"


int main()
{
    Context* context = new Context;

    std::stringstream stringstream("addi 10 5 20\nsubi 5 5 3\nj 1\nnop 0\nnop 0");

    InstructionFetch instructionFetch(stringstream, *context);
    InstructionDecode instructionDecode(*context);
    Execution execution(*context);
    MemoryStage memoryStage(*context);
    WriteBack writeBack(*context);

    tbb::pipeline* pipeline = new tbb::pipeline();
    pipeline->add_filter(instructionFetch);
    pipeline->add_filter(instructionDecode);
    pipeline->add_filter(execution);
    pipeline->add_filter(memoryStage);
    pipeline->add_filter(writeBack);
    pipeline->run(1);

    delete(context);
    return 0;
}

