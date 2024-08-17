#include <iostream>

class base
{
    public:
    base ()
    {
        std::cout << "base::base\n";
    }
    virtual void print () const
    {
        std::cout << "base::print\n";
    }
    virtual ~ base ()
    {
        std::cout << "base::~base\n";
    }
};

class derived:public base
{
    public:
    derived ()
    {
        std::cout << "derived::derived\n";
    }
    void print () const override
    {
        std::cout << "derived::print\n";
    }
    ~derived ()
    {
        std::cout << "derived::~derived\n";
    }
};

void test1 (const base & p)
{
    std::cout << "-- test1 --\n";
    p.print ();
    std::cout<<"-----------\n";
}

void test2 (const base p)
{
    std::cout << "-- test2 --\n";
    p.print ();
    std::cout<<"-----------\n";
}

void test3 (base* p)
{
    std::cout << "-- test3 --\n";
    p->print ();
    std::cout<<"-----------\n";
}


int main ()
{
    std::cout << "Start\n";
    derived derivedObj;
    test1 (derivedObj);
    test2 (derivedObj);
    
    std::cout<<"Create basePtr to store derived obj\n";
    base *basePtr = new derived ();
    test3 (basePtr);
    std::cout<<"Delete basePtr\n";
    delete basePtr;
    
    std::cout << "End\n";
}

/*----------------------------- output -------------------------------------
Start
base::base
derived::derived
-- test1 --
derived::print
-----------
-- test2 --
base::print
-----------
base::~base
Create basePtr to store derived obj
base::base
derived::derived
-- test3 --
derived::print
-----------
Delete basePtr
derived::~derived
base::~base
End
derived::~derived
base::~base

*/
