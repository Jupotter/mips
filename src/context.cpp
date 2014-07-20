#include "context.hh"
#include <istream>

int Context::getInstructionCount() const
{
    return _instruction_count;
}

void Context::endInstruction()
{
    _instruction_count++;
}

unsigned int Context::getPC() const
{
    return _pc;
}

void Context::setPC(unsigned int value)
{
    _pc = value;
}

RegisterFile& Context::getRegisters() const
{
    return *_registers;
}

std::mutex& Context::getCoutMutex() const
{
    return *_mutex;
}

Context::Context()
{
    _mutex = new std::mutex();
    _registers = new RegisterFile();
}

Context::~Context()
{
    delete(_mutex);
    delete(_registers);
}
