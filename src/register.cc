#include "register.hh"

Register::Register(std::string name, int value, bool rp_load)
{
  this->_name = name;
  this->_value = value;
  this->_rp_load = rp_load;
}

int Register::load(void)
{
  return this->_value;
}

void Register::store(int value)
{
  if (this->_name != "$zero")
    this->_value = value;
}

std::string Register::getName(void)
{
  return this->_name;
}
