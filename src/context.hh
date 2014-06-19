#ifndef CONTEXT_HH
# define CONTEXT_HH

class Context
{
    private:
        int _cycle_count = 0;

    public:
        int getCycleCount() const;
        void startNewCycle();
};

#endif /* !CONTEXT_HH */
