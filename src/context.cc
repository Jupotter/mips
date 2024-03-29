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

bool Context::getPCChanged() const
{
    return _pc_changed || _ended;
}

unsigned int Context::getPC() const
{
    return _pc;
}

void Context::setPC(unsigned int value)
{
    while (_reset_check 
            < (RESET_CHECK_NUM < _cycle_count ? RESET_CHECK_NUM : _cycle_count)
            - ((_stall_num != 0 ? 2 : 1) + _cycles_since_end));
    _reset = false;
    _pc_changed = true;
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
    if (_stalled_stage != NONES)
        _stall_num = (int)_stalled_stage;
    _stalled_stage = NONES;
    if (_stall_num != 0)
        _stall_num++;
    if (_stall_num > WBS)
        _stall_num = 0;

    _pc_changed = false;
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
    while (_reset_check <
            (RESET_CHECK_NUM < _cycle_count ? RESET_CHECK_NUM : _cycle_count)
            - ((_stall_num != 0 ? 2 : 1) + _cycles_since_end));
    _mutex->lock();
    _cycles_ended++;
    _mutex->unlock();
}

bool Context::isMEMThreadFinished()
{
  if (_is_MEM_thread_finished)
    {
      _is_MEM_thread_finished = false;
      return true;
    }

  return false;
}

bool Context::isWBThreadFinished()
{
  if (_is_WB_thread_finished)
    {
      _is_WB_thread_finished = false;
      return true;
    }

  return false;
}

void Context::setMEMThreadState(bool state)
{
  _is_MEM_thread_finished = state;
}

void Context::setWBThreadState(bool state)
{
  _is_WB_thread_finished = state;
}

bool Context::cycleEnded()
{
    _mutex->lock();
    bool ret = _cycles_ended >
        (RESET_CHECK_NUM < _cycle_count ? RESET_CHECK_NUM : _cycle_count)
        - ((_stall_num != 0 ? 2 : 1) + _cycles_since_end);
    _mutex->unlock();
    return ret;
}

StageNumber Context::getStalledStage() const
{
    return _stalled_stage;
}

void Context::stall(StageNumber stage)
{
    _stalled_stage = stage;
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
