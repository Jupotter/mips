#ifndef PIPELINE_STAGE_HH
# define PIPELINE_STAGE_HH

#include "pipeline.hh"
#include "context.hh"
#include "interstage.hh"

class Context;

class PipelineStage
{
    private:
        Interstage* _in_interstage;

        virtual Interstage* process(Interstage* input) = 0;

    protected:
        static p::pipeline* PIPELINE;

        Context& _contexte;

    public:
        static void SetPipeline(p::pipeline* p);

        PipelineStage(Context& contexte);

        void* operator()(void* input);
        Interstage* getInterstage();
};

#endif /* !PIPELINE_STAGE_HH */
