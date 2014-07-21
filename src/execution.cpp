#include "execution.hh"

Interstage* Execution::process(Interstage* input)
{
    while (_contexte.isReset() == false);

    #ifdef DEBUG
    _contexte.getCoutMutex().lock();
    std::cout
        << PIPELINE->t_get() << ":EXE: " << *input->instruction << std::endl;
    _contexte.getCoutMutex().unlock();
    #endif

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
        case LW:
            result = op1 + op2;
            break;
        case SW:
            result = op1 + op2;
            break;
        default:
            result = 0;
            break;
    }
    input->pc += input->immed;
    input->result = result;

//    while (_contexte.pc_changed == false);
    if (input->jump)
        _contexte.setPC(input->pc);

    _contexte.endCycle();
    while (_contexte.cycleEnded() == false);

    return input;
}

Execution::Execution(Context& context)
    : PipelineStage(context)
{
    _contexte.registerStage(this, EXS);
}
