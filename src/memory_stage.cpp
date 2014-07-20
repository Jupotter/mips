#include "memory_stage.hh"

MemoryStage::MemoryStage(Context& context)
    : PipelineStage(context)
{ }

Interstage* MemoryStage::process(Interstage* input)
{
    while (_contexte.isReset() == false);
    _contexte.getCoutMutex().lock();
    std::cout <<
        PIPELINE->t_get() << ":MEM: " << *input->instruction << std::endl;
    _contexte.getCoutMutex().unlock();

    if (input->memoryWrite)
    {
        // input->op2 == input->data
        _memory[input->result] = input->data;
        return input;
    }

    input->data = _memory[input->result % 1024];
    return input;
}
