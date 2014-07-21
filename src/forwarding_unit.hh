#ifndef FORWARDING_UNIT_HH
# define FORWARDING_UNIT_HH

# include "context.hh"
# include "interstage.hh" 

class ForwardingUnit
{
    private:
        Context& _contexte;

    public:
        bool forward_mem_op1();
        bool forward_mem_op2();
        bool forward_wb_op1();
        bool forward_wb_op2();
        
        int  getMEMreg();
        int  getWBreg();
        ForwardingUnit(Context& contexte);
};

#endif /* !FORWARDING_UNIT_HH */
