#ifndef PIPELINE_STAGE_HH
# define PIPELINE_STAGE_HH

#include "tbb/pipeline.h"
#include "context.hh"
#include "interstage.hh"

class PipelineStage : public tbb::filter
{
    private:
        Context _contexte;
        virtual Interstage* process(Interstage* input) = 0;


    public:
        PipelineStage(Context contexte);

        void* operator()(void* input);
};

#endif /* !PIPELINE_STAGE_HH */
