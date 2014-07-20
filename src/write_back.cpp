#include "write_back.hh"

#include <iostream>

WriteBack::WriteBack(Context& context)
: PipelineStage(context)
{ }


Interstage* WriteBack::process(Interstage* input)
{
    std::cout << input->result << std::endl;
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

    // DEBUG
    _contexte.getRegisters().dump();
    return NULL;
}
