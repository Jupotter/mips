#ifndef CONTEXT_HH
# define CONTEXT_HH

class Context
{
    private:
        int _cycle_count = 0;
        unsigned int _pc = 0;

    public:
        int getCycleCount() const;
        void startNewCycle();
        unsigned int getPC() const;
        void setPC(unsigned int value);

        Context();
};

#endif /* !CONTEXT_HH */
