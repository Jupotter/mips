#include "execution.hh"

Interstage* Execution::process(Interstage* input)
{
    int op1 = input->op1;
    int op2 = input->op2;
    Operations op = input->op;

    int result = 0;

    switch (op)
    {
        case ADD:
            result = op1 + op2;
            break;
        case SUB:
            result = op1 - op2;
            break;
        default:
            result = 0;
            break;
    }
    input->pc += input->immed << 2;
    input->result = result;
    return input;
}

Execution::Execution(Context& context)
    : PipelineStage(context)
{ }
