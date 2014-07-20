#ifndef CONTEXT_HH
# define CONTEXT_HH

#include <mutex>
#include "register_file.hh"

class Context
{
    private:
        int _instruction_count = 0;
        unsigned int _pc = 1;
        RegisterFile* _registers;

        std::mutex* _mutex;


    public:
        int getInstructionCount() const;
        void endInstruction();
        unsigned int getPC() const;
        void setPC(unsigned int value);
        RegisterFile& getRegisters() const;
        std::mutex& getCoutMutex() const;

        Context();
        ~Context();
};

#endif /* !CONTEXT_HH */
