#ifndef MEMORY_STAGE_HH
# define MEMORY_STAGE_HH

#include "pipeline_stage.hh"

class MemoryStage : public PipelineStage
{
    private:
        unsigned int _memory[1024];
        Interstage* process(Interstage* input);

    public:
        MemoryStage(Context& context);
        void dump(void);
};

#endif /* !MEMORY_STAGE_HH */
