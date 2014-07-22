#include "pipeline_stage.hh"

p::pipeline* PipelineStage::PIPELINE = NULL;

void PipelineStage::SetPipeline(p::pipeline* p)
{
    PIPELINE = p;
}

PipelineStage::PipelineStage(Context& contexte, StageNumber type)
    : _contexte(contexte), _type(type)
{
    _contexte.registerStage(this, type);
}

void* PipelineStage::operator()(void* input)
{
    if (!_stalled)
        _interstage = (Interstage*)input;

    Interstage* ret = process(_interstage);

    StageNumber stall = _contexte.getStalledStage();
    if (stall != NONES && stall >= _type)
    {
        _stalled = true;
        if (stall == _type)
            return p::latch::noop;
        return ret;
    }

    _stalled = false;
    return ret;
}

Interstage* PipelineStage::getInterstage()
{
    return _interstage;
}
