#ifndef INSTRUCTION_FETCH_HH
# define INSTRUCTION_FETCH_HH

#include <istream>
#include <vector>
#include <string>
#include "pipeline_stage.hh"

class InstructionFetch : public PipelineStage
{
    private:
        std::istream& _file;
        virtual Interstage* process(Interstage* input);
        std::vector<std::string*> _history;

    public:
        InstructionFetch(std::istream& file, Context& context);
        ~InstructionFetch();

};

#endif /* !INSTRUCTION_FETCH_HH */
