#ifndef INSTRUCTION_DECODE_HH
# define INSTRUCTION_DECODE_HH

#include "pipeline_stage.hh"
#include <string>

enum InstructionType
{
    R_TYPE,
    I_TYPE,
    J_TYPE,

};

class InstructionDecode : public PipelineStage
{
    private:
        Operations _op;
        InstructionType _type;
        void decodeOperation(std::string& operation);
        Interstage* process(Interstage* input);


    public:
        InstructionDecode(Context& context);
};

#endif /* !INSTRUCTION_DECODE_HH */
