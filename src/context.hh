#ifndef CONTEXT_HH
# define CONTEXT_HH

#include "register_file.hh"

class Context
{
    private:
        int _cycle_count = 0;
        unsigned int _pc = 1;
        RegisterFile* _registers;


    public:
        int getCycleCount() const;
        void startNewCycle();
        unsigned int getPC() const;
        void setPC(unsigned int value);
        RegisterFile& getRegisters() const;

        Context();
        ~Context();
};

#endif /* !CONTEXT_HH */
