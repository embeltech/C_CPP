#include <iostream>
class base{
    //__vptr pointer to VTable of base class
    public:
    //CTOR
    /*There is no virtual CTOR : Virtual keywork comes into effect for derived class object when stored in base class pointer.
      Due to virtual keyword the linker accesses the VTABLE of derived class object.
      Since at the time of CTOR call its not possible to have VTABLE as object itself is being constructed. 
      Since there is no object hence no VTABLE hence not possible to have virtual CTOR
    */
    base()
    {
        std::cout<<"Base CTOR\n";
    }
    virtual void function1()
    {
        std::cout<<"Base function1\n";
    }
    virtual void function2()
    {
        std::cout<<"Base function2\n";
    }
    virtual void function3()
    {
        std::cout<<"Base function3\n";
    }
    //DTOR -> destroy derived class part then destroy base class part of derived class object.
    //virtual keyword required when base class pointer(bptr) stores derived class object and delete bptr is invoked.
    //then derived Dtor is called first for derived part of obj then base dtor is called for base part of derived object
    //destruction should happen in reverse order -> destroy derived part then destroy base part.
    virtual ~base()  
    {
        std::cout<<"Base DTOR\n";
    }
};

/*    Derived object has two parts : Base class inherited part + new derived part.
*     Derived class pointer can see both parts
*     Base class pointer can see only base class part. (Base class pointer pointing to derived class object)
*     To make base class pointer to see both parts use virtual keyword for functions. So it creates VTABLE.
*     Base class pointer pointing to derived class object with VTABLE of derived object is referred and function call is resolved properly
*/

class derived1: public base
{
    //__vptr pointer to VTable of derived1 class
    public:
    derived1()  //calls base CTOR first then derived CTOR. as object construction begins from base class part then derived part is constructed
    {
        std::cout<<"derived1 CTOR\n";
    }
    //int function1()   -> this could lead to new function of derived class instead of overriding. Adding override keyword will give compilation error
    void function1() override //override keyword is to make sure you override exact virtual function of base class.
    {
        std::cout<<"derived1 function1\n";
    }
    ~derived1()
    {
        std::cout<<"derived1 DTOR\n";
    }
};
class derived2: public base
{
    //__vptr pointer to VTable of derived2 class
    public:
    derived2()
    {
        std::cout<<"derived2 CTOR\n";
    }
    void function2() override // // in VTable this call resolves to derived2::function2(), other calls resolves to base::function1(),base::function3()
    {
        std::cout<<"derived2 function2\n";
    }
    ~derived2()
    {
        std::cout<<"derived2 DTOR\n";
    }
};


int main()
{
   
    base *bptr = new base(); 
    bptr->function3();
    delete bptr;                //calls base DTOR
    
    std::cout<<"----- derived1 object in derived1 pointer -------\n";
    derived1 *d1ptr = new derived1();
    delete d1ptr;
    
    std::cout<<"----- derived1 object in base pointer -------\n";
    bptr = new derived1();
    bptr->function1();          //__vptr -> VTable  of derived1 class -> derived1::function1() as it is overridden
    bptr->function2();          //__vptr -> VTable  of derived1 class -> base::function2()
    bptr->function3();          //__vptr -> VTable  of derived1 class -> base::function3()
    delete bptr;               //calls base DTOR if base class DTOR is non virtual 
    
    std::cout<<"----- derived2 object in base pointer -------\n";
    bptr = new derived2();
    bptr->function1();          //__vptr -> VTable  of derived2 class -> base::function1() 
    bptr->function2();          //__vptr -> VTable  of derived2 class -> derived2::function2() as it is overridden
    bptr->function3();          //__vptr -> VTable  of derived2 class -> base::function3()
    delete bptr;               //calls base DTOR if base class DTOR is non virtual

    std::cout<<"----- derived2 object in base class variable b2 (object slicing) -------\n";
    // calls derived2() CTOR and temp object is created and destroyed immediately.
    base b2 = derived2();       //Only base part of derived2 is copied to base class object
    b2.function1();             //base::function1()
    b2.function2();             //base::function2() is called as b2 contains base part only
    b2.function3();             //base::function3()
    
    return 0;
    //base DTOR for b2 will be called
}

//----------------------------------------------- Output ---------------------------------------
/*

Base CTOR
Base function3
Base DTOR
----- derived1 object in derived1 pointer -------
Base CTOR
derived1 CTOR
derived1 DTOR
Base DTOR        -> works even when virtual is not used for ~base() as derived class pointer stores derived class object
----- derived1 object in base pointer -------
Base CTOR
derived1 CTOR
derived1 function1
Base function2
Base function3
derived1 DTOR
Base DTOR
----- derived2 object in base pointer -------
Base CTOR
derived2 CTOR
Base function1
derived2 function2
Base function3
derived2 DTOR
Base DTOR
----- derived2 object in base class variable b2 (object slicing) -------
Base CTOR
derived2 CTOR
derived2 DTOR
Base DTOR
Base function1
Base function2
Base function3
Base DTOR    -> b2 object

*/
