#include "pipeline_stage.hh"

PipelineStage::PipelineStage(Context& contexte)
    : filter(tbb::filter::serial_in_order), _contexte(contexte)
{ }

void* PipelineStage::operator()(void* input)
{
    return (process((Interstage*)input));
}
