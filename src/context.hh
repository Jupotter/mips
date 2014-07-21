#ifndef CONTEXT_HH
# define CONTEXT_HH

#include <mutex>
#include "register_file.hh"

class PipelineStage;
class Interstage;

enum StageNumber
{
    IFS,
    IDS,
    EXS,
    MEMS,
    WBS,
};

class Context
{
    private:
        static const int RESET_CHECK_NUM = 5;

        int _instruction_count = 0;
        int _cycle_count = 0;
        unsigned int _pc = 1;
        bool _pc_changed;
        RegisterFile* _registers;
        bool _reset = false;
        bool _ended = false;
        int _reset_check = 0;
        int _cycles_ended = 0;
        int _cycles_since_end = 0;
        std::mutex* _mutex;

        PipelineStage* _stages[5];

        void reset_no_lock();

    public:

        int getInstructionCount() const;
        void endInstruction();
        bool getPCChanged() const;
        unsigned int getPC() const;
        void setPC(unsigned int value);
        RegisterFile& getRegisters() const;
        std::mutex& getCoutMutex() const;

        void reset();
        void end();
        bool isReset();
        void endCycle();
        bool cycleEnded();

        void stall(unsigned int number);
        Interstage* getInterstage(StageNumber stage);

        void registerStage(PipelineStage* stage, StageNumber number);

        Context();
        ~Context();
};

#endif /* !CONTEXT_HH */
