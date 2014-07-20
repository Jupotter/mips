#ifndef CONTEXT_HH
# define CONTEXT_HH

#include <mutex>
#include "register_file.hh"

class Context
{
    private:
        static const int RESET_CHECK_NUM = 5;

        int _instruction_count = 0;
        int _cycle_count = 0;
        unsigned int _pc = 1;
        RegisterFile* _registers;
        bool _reset = false;
        bool _ended = false;
        int _reset_check = 0;

        std::mutex* _mutex;

        void reset_no_lock();

    public:
        bool pc_changed;
        int getInstructionCount() const;
        void endInstruction();
        unsigned int getPC() const;
        void setPC(unsigned int value);
        RegisterFile& getRegisters() const;
        std::mutex& getCoutMutex() const;
        void reset();
        void end();
        bool isReset();

        Context();
        ~Context();
};

#endif /* !CONTEXT_HH */
