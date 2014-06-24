#include "instruction_decode.hh"

#include <vector>
#include <iterator>
#include <istream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "operations.hh"

InstructionDecode::InstructionDecode(Context& context)
    : PipelineStage(context)
{ }

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

Interstage* InstructionDecode::process(Interstage* input)
{
    std::vector<std::string> tokens = split(*input->instruction, ' ');

    std::string operation = tokens[0];
    std::transform(operation.begin(),
            operation.end(),
            operation.begin(),
            ::toupper);

    if (operation.compare("ADD") == 0)
        input->op= ADD;
    else if (operation.compare("SUB") == 0)
        input->op= SUB;
    else
    {
        std::cerr << "Error, unkown operation " << operation << std::endl;
    }

    input->immed = 0;
    input->memoryWrite = false;
    input->writeData = true;
    return input;
}
