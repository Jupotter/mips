#ifndef PIPELINE_STAGE_HH
# define PIPELINE_STAGE_HH

#include "pipeline.hh"
#include "context.hh"
#include "interstage.hh"

class Context;

class PipelineStage
{
    private:
        Interstage* _interstage;

        virtual Interstage* process(Interstage* input) = 0;

    protected:
        static p::pipeline* PIPELINE;

        Context& _contexte;
        StageNumber _type;
        bool _stalled = false;

    public:
        static void SetPipeline(p::pipeline* p);

        PipelineStage(Context& contexte, StageNumber type);

        void* operator()(void* input);
        Interstage* getInterstage();
};

#endif /* !PIPELINE_STAGE_HH */
