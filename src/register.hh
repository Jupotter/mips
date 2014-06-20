#ifndef REGISTER_HH
# define REGISTER_HH

# include <string>

class Register
{
private:
  std::string _name;
  int _value;
  bool _rp_load;

public:
  Register(std::string name, int value, bool rp_load);
  int load(void);
  void store(int value);
  std::string getName(void);
};

#endif /* !REGISTER_HH */
