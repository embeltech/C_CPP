#include <iostream>

class Robot
{
public:
  Robot ()
  {
	std::cout << "Robot::Robot\n";
  }

  virtual void trace () const
  {
	std::cout << "Robot::trace\n";
  }
  virtual ~ Robot ()
  {
	std::cout << "Robot::~Robot\n";
  }
};

class Hexapod:public Robot
{
public:
  Hexapod ()
  {
	std::cout << "Hexapod::Hexapod\n";
  }
  void trace () const override
  {
	std::cout << "Hexapod::trace\n";
  }
   ~Hexapod ()
  {
	std::cout << "Hexapod::~Hexapod\n";
  }
};

void
f (const Robot & p)
{
  p.trace ();
}

void
g (const Robot p)
{
  p.trace ();
}

void h (Robot* p)
{
  p->trace ();
}


int main ()
{
  std::cout << "Start\n";
  Hexapod lwr;
  f (lwr);
  g (lwr);
  

  Robot *robot = new Hexapod ();
  h (robot);
  delete robot;
  
  std::cout << "End\n";
}
