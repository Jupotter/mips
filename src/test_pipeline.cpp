#include <sstream>
#include "pipeline.hh"
#include "context.hh"
#include "instruction_fetch.hh"
#include "instruction_decode.hh"
#include "execution.hh"
#include "memory_stage.hh"
#include "write_back.hh"


int main()
{
    Context* context = new Context;

    std::stringstream stringstream("addi 10 5 20\nsubi 5 5 3\nj -1\nnop 0\nnop 0\nnop 0");
    //std::stringstream stringstream("addi 10 5 20)\nsubi 5 5 3");
    //std::stringstream stringstream("addi 10 5 20\naddi 10 4 3\nsw 4 5 0\nlw 5 8 0");

    InstructionFetch instructionFetch(stringstream, *context);
    InstructionDecode instructionDecode(*context);
    Execution execution(*context);
    MemoryStage memoryStage(*context);
    WriteBack writeBack(*context);

    p::pipeline pipeline;
    PipelineStage::SetPipeline(&pipeline);

    pipeline.add_stage(std::ref(instructionFetch))
        .add_stage(std::ref(instructionDecode))
        .add_stage(std::ref(execution))
        .add_stage(std::ref(memoryStage))
        .add_stage(std::ref(writeBack));

    pipeline.run();

    context->getRegisters().dump();
    int cycles = pipeline.t_get() - 1;
    int instructions = context->getInstructionCount();
    std::cout
        << "Total Number of Cycles = " << cycles << std::endl
        << "Total Number of instructions = " << instructions << std::endl
        << "Average CPI = " << cycles / (float)instructions << std::endl
        << "Average IPC = " << instructions / (float)cycles << std::endl;
    delete(context);
    return 0;
}

