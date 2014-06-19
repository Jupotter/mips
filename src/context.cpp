#include "context.hh"

int Context::getCycleCount() const
{
    return _cycle_count;
}

void Context::startNewCycle()
{
    _cycle_count++;
}
