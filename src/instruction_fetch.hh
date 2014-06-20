#ifndef INSTRUCTION_FETCH_HH
# define INSTRUCTION_FETCH_HH

#include <istream>
#include "pipeline_stage.hh"

class InstructionFetch : public PipelineStage
{
    private:
        std::istream& _file;
        virtual Interstage* process(Interstage* input);

    public:
        InstructionFetch(std::istream& file, Context& context);

};

#endif /* !INSTRUCTION_FETCH_HH */
