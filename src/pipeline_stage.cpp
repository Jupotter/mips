#include "pipeline_stage.hh"

p::pipeline* PipelineStage::PIPELINE = NULL;

PipelineStage::PipelineStage(Context& contexte)
    : _contexte(contexte)
{ }

void* PipelineStage::operator()(void* input)
{
    Interstage* ret = process((Interstage*)input);
    return ret;
}

void PipelineStage::SetPipeline(p::pipeline* p)
{
    PIPELINE = p;
}
