#include "pipeline_stage.hh"

p::pipeline* PipelineStage::PIPELINE = NULL;

void PipelineStage::SetPipeline(p::pipeline* p)
{
    PIPELINE = p;
}

PipelineStage::PipelineStage(Context& contexte)
    : _contexte(contexte)
{ }

void* PipelineStage::operator()(void* input)
{
    _in_interstage = (Interstage*)input;
    Interstage* ret = process(_in_interstage);
    return ret;
}

Interstage* PipelineStage::getInterstage()
{
    return _in_interstage;
}
