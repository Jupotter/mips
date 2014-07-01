#ifndef REGISTER_FILE_HH
# define REGISTER_FILE_HH

# include <string>
# include <iostream>
# include <array>
# include "register.hh" 

class RegisterFile
{
private:
  Register* _decoder[32];

public:
  RegisterFile();
  ~RegisterFile();
  void dump(void);
  Register* getRegister(int index) const;

};

#endif /* !REGISTER_FILE_HH */
