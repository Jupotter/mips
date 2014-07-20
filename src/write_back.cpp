#include "write_back.hh"

#include <iostream>

    WriteBack::WriteBack(Context& context)
: PipelineStage(context)
{ }


Interstage* WriteBack::process(Interstage* input)
{
    _contexte.getCoutMutex().lock();
    std::cout
        << PIPELINE->t_get() << ":WB:" << *input->instruction << std::endl;
    _contexte.getCoutMutex().unlock();

    if (!input->memoryWrite)
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
    delete input;

    _contexte.endInstruction();

//    // DEBUG
//    _contexte.getCoutMutex().lock();
//    _contexte.getRegisters().dump();
//    _contexte.getCoutMutex().unlock();
    return input;
}
