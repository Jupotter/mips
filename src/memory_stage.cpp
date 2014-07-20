#include "memory_stage.hh"

MemoryStage::MemoryStage(Context& context)
    : PipelineStage(context)
{ }

Interstage* MemoryStage::process(Interstage* input)
{
    #ifdef DEBUG
    _contexte.getCoutMutex().lock();
    std::cout <<
        PIPELINE->t_get() << ":MEM: " << *input->instruction << std::endl;
    _contexte.getCoutMutex().unlock();
    #endif

    if (input->jump)
    {
        _contexte.setPC(input->pc);
    }
    if (input->memoryWrite)
    {
        // input->op2 == input->data
        _memory[input->result] = input->data;
        return input;
    }

    input->data = _memory[input->result % 1024];
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
