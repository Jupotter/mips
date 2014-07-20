#include <string>
#include "instruction_fetch.hh"

InstructionFetch::InstructionFetch(std::istream& file, Context& context)
    : PipelineStage(context), _file(file)
{
    std::string* line = new std::string("nop 0 0 0");
    _history.push_back(line);
}

Interstage* InstructionFetch::process(Interstage* input)
{
    unsigned int pc = _contexte.getPC();
    std::string* line;

    while (pc >= _history.size())
    {
        line = new std::string();
        if (0 == std::getline(_file, *line))
            return (Interstage*)p::latch::terminate;
        _history.push_back(line);
    }

    line = _history[pc];

    #ifdef DEBUG
    _contexte.getCoutMutex().lock();
    std::cout
        << PIPELINE->t_get() << ":IF: " << *line << std::endl;
    _contexte.getCoutMutex().unlock();
    #endif

    Interstage* ret = new Interstage;
    ret->pc = pc + 1;
    _contexte.setPC(pc + 1);
    ret->instruction = line;
    ret->jump = false;
    return ret;
}

