#ifndef PIPELINE_STAGE_HH
# define PIPELINE_STAGE_HH

#include "pipeline.hh"
#include "context.hh"
#include "interstage.hh"

class PipelineStage
{
    protected:
        static p::pipeline* PIPELINE;

        Context& _contexte;
        virtual Interstage* process(Interstage* input) = 0;


    public:
        static void SetPipeline(p::pipeline* p);

        PipelineStage(Context& contexte);

        void* operator()(void* input);
};

#endif /* !PIPELINE_STAGE_HH */
