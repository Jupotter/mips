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
        Operations op;
        int result;
        int immed;  // if no immediate -> 0
};

#endif /* !INTERSTAGE_HH */
