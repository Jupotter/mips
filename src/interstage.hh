#ifndef INTERSTAGE_HH
# define INTERSTAGE_HH

#include <string>
#include "operations.hh"

struct Interstage
{

    public:
        unsigned int pc;
        std::string* instruction;

        int op1;    // rs
        int op2;    // rt ou immediat, suivant les cas
        int rs;    // Numero de registre rs
        int rt;    // Numero de registre rt
        Operations op;
        int result; // result from the ALU
        int immed;  // if no immediate -> 0

        bool memoryWrite; // do I write or read in memory?
        int data; // Data read from or written to memory

        int write_reg;

        bool writeData; // Write data or write result to register?

        bool jump; // Do this instruction change PC?
};

#endif /* !INTERSTAGE_HH */
