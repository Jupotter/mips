#ifndef INSTRUCTION_DECODE_HH
# define INSTRUCTION_DECODE_HH

#include "pipeline_stage.hh"

class InstructionDecode : public PipelineStage
{
    private:
        Interstage* process(Interstage* input);

    public:
        InstructionDecode(Context& context);
};

#endif /* !INSTRUCTION_DECODE_HH */
