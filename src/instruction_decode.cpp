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

std::string toUpper(std::string input)
{
    std::transform(input.begin(),
            input.end(),
            input.begin(),
            ::toupper);

    return input;
}

void InstructionDecode::decodeOperation(std::string& operation)
{
    if (operation.compare("ADD") == 0)
    {
        _type = R_TYPE;
        _op= ADD;
    }
    else if (operation.compare("ADDI") == 0)
    {
        _type = I_TYPE;
        _op= ADD;
    }
    else if (operation.compare("SUB") == 0)
    {
        _type = R_TYPE;
        _op= SUB;
    }
    else if (operation.compare("SUBI") == 0)
    {
        _type = I_TYPE;
        _op= SUB;
    }
    else
    {
        std::cerr << "Error, unkown operation " << operation << std::endl;
    }
}

Interstage* InstructionDecode::process(Interstage* input)
{
    std::vector<std::string> tokens = split(*input->instruction, ' ');

    std::string operation = toUpper(tokens[0]);

    decodeOperation(operation);

    input->op = _op;

    if (_type == R_TYPE)
    {
        int reg1 = std::stoi(tokens[1]);
        input->op1 = _contexte.getRegisters().getRegister(reg1)->load();
        int reg2 = std::stoi(tokens[2]);
        input->op2 = _contexte.getRegisters().getRegister(reg2)->load();
        input->write_reg = std::stoi(tokens[3]);
        input->immed = 0;
    }
    else if (_type == I_TYPE)
    {
        int reg1 = std::stoi(tokens[1]);
        input->op1 = _contexte.getRegisters().getRegister(reg1)->load();
        input->write_reg = std::stoi(tokens[2]);
        input->op2 = std::stoi(tokens[3]);
        input->immed = input->op2;
    }

    input->memoryWrite = false;
    input->writeData = true;
    return input;
}
