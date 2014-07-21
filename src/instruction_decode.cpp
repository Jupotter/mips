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
{
    _contexte.registerStage(this, IDS);
}

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

void InstructionDecode::decodeOperation(std::string& operation, Interstage* input)
{
    _jump = false;
    input->memoryWrite = false;
    input->writeData = false;

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
    else if (operation.compare("J") == 0)
    {
        _type = J_TYPE;
        _op = NOP;
        _jump = true;
    }
    else if (operation.compare("BEQ") == 0)
    {
        _type = I_TYPE;
        _op = EQ;
        _jump = true;
    }
    else if (operation.compare("BNEQ") == 0)
    {
        _type = I_TYPE;
        _op = NEQ;
        _jump = true;
    }
    else if (operation.compare("NOP") == 0)
    {
        _type = J_TYPE;
        _op = NOP;
    }
    else if (operation.compare("LW") == 0)
    {
        _type = I_TYPE;
        _op = LW;
        input->writeData = true;
    }
    else if (operation.compare("SW") == 0)
    {
        _type = I_TYPE;
        _op = SW;
        input->memoryWrite = true;
    }
    else
    {
        std::cerr << "Error, unkown operation " << operation << std::endl;
    }
}

Interstage* InstructionDecode::process(Interstage* input)
{
    while (_contexte.isReset() == false);
    #ifdef DEBUG
    _contexte.getCoutMutex().lock();
    std::cout
        << PIPELINE->t_get() << ":ID: " << *input->instruction << std::endl;
    _contexte.getCoutMutex().unlock();
    #endif

    std::vector<std::string> tokens = split(*input->instruction, ' ');

    std::string operation = toUpper(tokens[0]);

    decodeOperation(operation, input);

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
        input->data = _contexte.getRegisters().getRegister(input->write_reg)->load();
    }
    else if (_type == J_TYPE)
    {
        input->immed = std::stoi(tokens[1]);
        input->op1 = 0;
        input->op2 = 0;
        input->write_reg = 0;
    }
    input->jump = _jump;

    /* special jump circuit */
    while (!_contexte.getPCChanged());
    if (input->jump)
    {
        bool cond;
        switch (input->op)
        {
            case EQ:
                cond = input->op1 == input->data;
                break;
            case NEQ:
                cond = input->op1 != input->data;
                break;
            default:
                cond = true;
                break;
        }

        input->pc += input->immed;
        if (cond)
            _contexte.setPC(input->pc);
    }

    _contexte.endCycle();
    while (_contexte.cycleEnded() == false);

    return input;
}
