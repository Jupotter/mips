#include <string>
#include "instruction_fetch.hh"

InstructionFetch::InstructionFetch(std::istream& file, Context& context)
    : PipelineStage(context), _file(file)
{ }

Interstage* InstructionFetch::process(Interstage* input)
{
    std::string* line = new std::string();
    if (0 == std::getline(_file, *line))
        return NULL;

    unsigned int pc = _contexte.getPC();

    Interstage* ret = new Interstage;
    ret->pc = pc+4;
    ret->instruction = line;
    return ret;
}

