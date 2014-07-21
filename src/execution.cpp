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

    int op1;
    int op2;
    Operations op = input->op;

    ForwardingUnit fu(_contexte);

    int result = 0;

    while (_contexte.getInterstage(MEMS) != 0
	   && (!_contexte.isMEMThreadFinished()));
    while (_contexte.getInterstage(WBS) != 0
	   && (!_contexte.isWBThreadFinished()));

    if (fu.forward_mem_op1())
      {
	op1 = fu.getMEMreg();
	std::cout << "FwUnit : op1 override by mem_rt" << std::endl;
      }
    else if (fu.forward_wb_op1())
      {
	op1 = fu.getWBreg();
	std::cout << "FwUnit : op1 override by wb_rt" << std::endl;
      }
    else
      op1 = input->op1;

    if (!input->immed && fu.forward_mem_op2())
      {
	op2 = fu.getMEMreg();
       	std::cout << "FwUnit : op2 override by mem_rt" << std::endl;
      }
    else if (!input->immed && fu.forward_wb_op2())
      {
	op2 = fu.getWBreg();
	std::cout << "FwUnit : op2 override by wb_rt" << std::endl;
      }
    else
      op2 = input->op2;

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
        case EQ:
            result = op1 == op2;
            break;
        case NEQ:
            result = op1 != op2;
            break;
        default:
            result = 0;
            break;
    }
    input->result = result;

    _contexte.endCycle();
    while (_contexte.cycleEnded() == false);

    return input;
}

Execution::Execution(Context& context)
    : PipelineStage(context)
{
    _contexte.registerStage(this, EXS);
}
