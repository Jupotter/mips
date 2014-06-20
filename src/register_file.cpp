#include "register_file.hh"

RegisterFile::RegisterFile()
{
  for (int i = 0; i < 32; i++)
    {
      if (i == 0)
	this->_decoder[i] = (new Register("$zero", 0, false));
      else if (i == 1)
	this->_decoder[i] = (new Register("$at", 0, false));
      else if (i <= 3)
	this->_decoder[i] = (new Register(("$v" + std::to_string(i - 2)), 0, false));
      else if (i <= 7)
	this->_decoder[i] = (new Register(("$a" + std::to_string(i - 4)), 0, false));
      else if (i <= 15)
	this->_decoder[i] = (new Register(("$t" + std::to_string(i - 8)), 0, false));
      else if (i <= 23)
	this->_decoder[i] = (new Register(("$s" + std::to_string(i - 16)), 0, false));
      else if (i <= 25)
	this->_decoder[i] = (new Register(("$t" + std::to_string(i - (24 - 8))), 0, false));
      else if (i <= 27)
	this->_decoder[i] = (new Register(("$k" + std::to_string(i - 26)), 0, false));
      else if (i == 28)
	this->_decoder[i] = (new Register("$gp", 0, false));
      else if (i == 29)
	this->_decoder[i] = (new Register("$sp", 0, false));
      else if (i == 30)
	this->_decoder[i] = (new Register("$fp", 0, false));
      else if (i == 31)
	this->_decoder[i] = (new Register("$ra", 0, false));
    }
}

void RegisterFile::dump(void)
{
  std::cout << "-----" << std::endl
	    << "Dumping Register File" << std::endl;

  for (int i = 0; i < 32; i++)
    std::cout << this->_decoder[i]->getName() << " : " << this->_decoder[i]->load() << std::endl;

  std::cout << "End of dump Register File" << std::endl
	    << "-----" << std::endl;
}

RegisterFile::~RegisterFile()
{
  for (int i = 0; i < 32; i++)
    delete(this->_decoder[i]);
}
