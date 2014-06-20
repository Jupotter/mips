#include "context.hh"

int Context::getCycleCount() const
{
    return _cycle_count;
}

void Context::startNewCycle()
{
    _cycle_count++;
}

unsigned int Context::getPC() const
{
    return _pc;
}

void Context::setPC(unsigned int value)
{
    _pc = value;
}
