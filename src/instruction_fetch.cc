#include <string>
#include "instruction_fetch.hh"

InstructionFetch::InstructionFetch(std::istream& file, Context& context)
    : PipelineStage(context, IFS), _file(file)
{
    std::string* line = new std::string("nop 0");
    _history.push_back(line);
}

Interstage* InstructionFetch::process(Interstage* input)
{
#ifdef DEBUG
    _contexte.getCoutMutex().lock();
    std::cout << "---" << std::endl;
    _contexte.getCoutMutex().unlock();
#endif
    _contexte.reset();
    unsigned int pc = _contexte.getPC();
    if (_stalled)
        pc--;
    std::string* line;

    while (pc >= _history.size())
    {
        line = new std::string();
        if (0 == std::getline(_file, *line))
        {
            _contexte.setPC(pc + 1);
            _contexte.endCycle();
            while (_contexte.cycleEnded() == false);
            _contexte.end();
            return (Interstage*)p::latch::terminate;
        }
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

    _contexte.endCycle();
    while (_contexte.cycleEnded() == false);

    return ret;
}

InstructionFetch::~InstructionFetch()
{
    for (std::string* str : _history)
    {
        delete(str);
    }
    _history.clear();
}
