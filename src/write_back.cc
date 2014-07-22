#include "write_back.hh"

#include <iostream>

    WriteBack::WriteBack(Context& context)
: PipelineStage(context, WBS)
{ }


Interstage* WriteBack::process(Interstage* input)
{
    while (_contexte.isReset() == false);
    #ifdef DEBUG
    _contexte.getCoutMutex().lock();
    std::cout
        << PIPELINE->t_get() << ":WB:" << *input->instruction << std::endl;
    _contexte.getCoutMutex().unlock();
    #endif

    _contexte.setWBThreadState(false);

    if (!input->memoryWrite && !input->jump)
    {
        _contexte
            .getRegisters()
            .getRegister(input->write_reg)
            ->store(input->result);
    }
    else if (input->writeData)
    {
        _contexte
            .getRegisters()
            .getRegister(input->write_reg)
            ->store(input->data);
    }

    _contexte.endCycle();
    _contexte.setWBThreadState(true);
    while (_contexte.cycleEnded() == false);

    delete input;

    if (input->op != NOP)
    _contexte.endInstruction();

//    // DEBUG
//    _contexte.getCoutMutex().lock();
//    _contexte.getRegisters().dump();
//    _contexte.getCoutMutex().unlock();
    return input;
}
