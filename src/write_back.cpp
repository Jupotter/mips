#include "write_back.hh"

WriteBack::WriteBack(Context& context)
: PipelineStage(context)
{ }


Interstage* WriteBack::process(Interstage* input)
{

    delete input;
    return NULL;
}
