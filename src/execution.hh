#ifndef EXECUTION_HH
# define EXECUTION_HH

#include "pipeline_stage.hh"
#include "forwarding_unit.hh"

class Execution : public PipelineStage
{
    private:
        Interstage* process(Interstage* input);

    public:
        Execution(Context& context);
};

#endif /* !EXECUTION_HH */
