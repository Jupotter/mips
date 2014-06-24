#include "write_back.hh"

#include <iostream>

WriteBack::WriteBack(Context& context)
: PipelineStage(context)
{ }


Interstage* WriteBack::process(Interstage* input)
{
    std::cout << input->result << std::endl;
    delete input;
    return NULL;
}
