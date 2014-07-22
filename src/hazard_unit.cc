#include "hazard_unit.hh"

HazardUnit::HazardUnit(Context& context)
    : _context(context)
{ }

bool HazardUnit::checkHazard()
{
    Interstage* ids = _context.getInterstage(IDS);
    Interstage* exs = _context.getInterstage(EXS);

    // Error check, or if we start the pipeline
    if (!exs || !ids)
        return false;

    // No hazard if we write to memory or if we do not write back to a register
    if (!exs->writeData || exs->memoryWrite)
        return false;

    int id_rs = ids->rs;
    int id_rt = ids->rt;

    int ex_rt = exs->rt;

    if (ex_rt == id_rs || ex_rt == id_rt)
        return true;

    return false;
}
