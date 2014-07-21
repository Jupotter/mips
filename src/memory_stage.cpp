#include "memory_stage.hh"

MemoryStage::MemoryStage(Context& context)
    : PipelineStage(context, MEMS)
{ }

Interstage* MemoryStage::process(Interstage* input)
{
    while (_contexte.isReset() == false);
    #ifdef DEBUG
    _contexte.getCoutMutex().lock();
    std::cout <<
        PIPELINE->t_get() << ":MEM: " << *input->instruction << std::endl;
    _contexte.getCoutMutex().unlock();
    #endif

    if (input->memoryWrite)
    {
        // input->op2 == input->data
        _memory[input->result] = input->data;
    }
    else
    {
        input->data = _memory[input->result % 1024];
    }

    _contexte.endCycle();
    while (_contexte.cycleEnded() == false);

    return input;
}

void MemoryStage::dump(void)
{
  std::cout << "-----" << std::endl
            << "Dumping memory" << std::endl;
  for (int i = 0; i < 5; i++)
    {
      std::cout << i        << " : " << _memory[i]      << "\t\t"
		<< (i + 5)  << " : " << _memory[(i+5)]  << "\t\t"
	        << (i + 10) << " : " << _memory[(i+10)] << "\t\t"
	        << (i + 15) << " : " << _memory[(i+15)] << "\t\t"
	        << std::endl;
    }
  std::cout << "End of memory dump" << std::endl
            << "-----" << std::endl; 
}
