#include "forwarding_unit.hh"

ForwardingUnit::ForwardingUnit(Context& contexte)
    : _contexte(contexte)
{ }

bool ForwardingUnit::forward_mem_op1()
{
    if (_contexte.getInterstage(MEMS) != 0)
        return (!_contexte.getInterstage(MEMS)->jump &&
                !_contexte.getInterstage(MEMS)->memoryWrite &&
                (_contexte.getInterstage(EXS)->rs == _contexte.getInterstage(MEMS)->rt));
    else
        return false;
}

bool ForwardingUnit::forward_mem_op2()
{
    if (_contexte.getInterstage(MEMS) != 0)
        return (_contexte.getInterstage(MEMS)->jump &&
                !_contexte.getInterstage(MEMS)->memoryWrite &&
                (_contexte.getInterstage(EXS)->rt == _contexte.getInterstage(MEMS)->rt));
    else
        return false;
}

bool ForwardingUnit::forward_wb_op1()
{
    if (_contexte.getInterstage(WBS) != 0)
        return (_contexte.getInterstage(MEMS)->jump &&
                !_contexte.getInterstage(MEMS)->memoryWrite &&
                (_contexte.getInterstage(EXS)->rs == _contexte.getInterstage(WBS)->rt));
    else
        return false;
}

bool ForwardingUnit::forward_wb_op2()
{
    if (_contexte.getInterstage(WBS) != 0)
        return (_contexte.getInterstage(MEMS)->jump &&
                !_contexte.getInterstage(MEMS)->memoryWrite &&
                (_contexte.getInterstage(EXS)->rt == _contexte.getInterstage(WBS)->rt));
    else
        return false;
}

int ForwardingUnit::getMEMreg()
{
  return _contexte.getInterstage(MEMS)->result;
}

int ForwardingUnit::getWBreg()
{
  return _contexte.getInterstage(WBS)->result;
}
