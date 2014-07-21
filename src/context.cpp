#include "context.hh"
#include <istream>
#include "pipeline_stage.hh"

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
    while (_reset_check < (RESET_CHECK_NUM < _cycle_count
                ? RESET_CHECK_NUM : _cycle_count) - (1 + _cycles_since_end));
    _reset = false;
    pc_changed = true;
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

void Context::end()
{
    _mutex->lock();
    _ended = true;
    _cycles_since_end++;
    _mutex->unlock();
}

void Context::reset()
{
    _mutex->lock();
    reset_no_lock();
    _mutex->unlock();
}

void Context::reset_no_lock()
{
    pc_changed = false;
    _reset_check = 0;
    _cycle_count++;
    _cycles_ended = 0;
    _reset = true;
}

bool Context::isReset()
{
    _mutex->lock();
    if (_ended && !_reset)
    {
        reset_no_lock();
        _cycles_since_end++;
    }
    if (_reset)
    {
        _reset_check++;
        _mutex->unlock();
        return true;
    }
    _mutex->unlock();
    return false;
}

void Context::endCycle()
{
    while (_reset_check < (RESET_CHECK_NUM < _cycle_count
                ? RESET_CHECK_NUM : _cycle_count) - (1 + _cycles_since_end));
    _mutex->lock();
    _cycles_ended++;
    _mutex->unlock();
}

bool Context::cycleEnded()
{
    _mutex->lock();
    bool ret = _cycles_ended > (RESET_CHECK_NUM < _cycle_count
                ? RESET_CHECK_NUM : _cycle_count) - (1 + _cycles_since_end);
    _mutex->unlock();
    return ret;
}

Interstage* Context::getInterstage(StageNumber stage)
{
    return _stages[stage]->getInterstage();
}

void Context::registerStage(PipelineStage* stage, StageNumber number)
{
    _stages[number] = stage;
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
