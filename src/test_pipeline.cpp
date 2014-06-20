#include <sstream>
#include "tbb/pipeline.h"
#include "context.hh"
#include "instruction_fetch.hh"


int main()
{
    Context* context = new Context;

    std::stringstream stringstream("lw   $10, 20($1)\nsub  $11, $2, $3");

    InstructionFetch instructionFetch(stringstream, *context);

    tbb::pipeline* pipeline = new tbb::pipeline();
    pipeline->add_filter(instructionFetch);
    pipeline->run(5);

    delete(context);
    return 0;
}

