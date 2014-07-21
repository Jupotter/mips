#ifndef INSTRUCTION_DECODE_HH
# define INSTRUCTION_DECODE_HH

#include <string>
#include "pipeline_stage.hh"
#include "hazard_unit.hh"

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
        bool _jump;
        void decodeOperation(std::string& operation, Interstage* input);
        Interstage* process(Interstage* input);
        HazardUnit _hazard_unit;

    public:
        InstructionDecode(Context& context);
};

#endif /* !INSTRUCTION_DECODE_HH */
