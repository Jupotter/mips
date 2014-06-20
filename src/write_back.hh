#ifndef WRITE_BACK_HH
# define WRITE_BACK_HH

#include "pipeline_stage.hh"

class WriteBack : public PipelineStage
{
    private:
        Interstage* process(Interstage* input);

    public:
        WriteBack(Context& context);
};

#endif /* !WRITE_BACK_HH */
