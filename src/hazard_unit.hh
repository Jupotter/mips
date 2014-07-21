#ifndef HAZARD_UNIT_HH
# define HAZARD_UNIT_HH

#include "interstage.hh"
#include "context.hh"

class HazardUnit
{
    private:
        Context& _context;
    public:
        HazardUnit(Context& context);

        bool checkHazard();
};

#endif /* !HAZARD_UNIT_HH */
