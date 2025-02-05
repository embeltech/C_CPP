/*
*  # Rvalue: A temporary object that does not have memory location label (variable) 
*     (e.g., literals, temporary objects returned by functions, expression value etc). 
*  # Rvalue Reference: A reference that can bind object to an rvalue. It is declared using &&.
*  # Move Semantics: Allows transferring of the resources owned by an object to another object, rather than being copied.
*  # Move semantics is based on rvalue reference which enables binding object to rvalue then transfers(move) the resources from the source object to the newly constructed object 
*/


#include <iostream>
class Rectangle{
  private:
    int length;
    int breadth;

  public:
    Rectangle()=default;
    Rectangle(int x, float y):length(x),breadth(y)
    {
        std::cout<<"Parameterised CTOR : \n";
        display();  
    }
    /* Copy CTOR ALWAYS accepts object by reference only. If we use copy by value here it will call infinite loop of calling copy CTOR 
    * to pass argument object to construct parameter of copy CTOR
    *  Rectangle(const Rectangle obj)  --> not allowed
    */
    Rectangle(const Rectangle& obj)
    {
        length = obj.length;
        breadth = obj.breadth;
        std::cout<<"Copy CTOR : \n";
        display();  
    }
    void operator=(const Rectangle& obj)
    {
        length = obj.length;
        breadth = obj.breadth;
        std::cout<<"Copy Assignment : \n";
        display();
    }
    Rectangle(const Rectangle&& mvobj) noexcept
    {
        length = mvobj.length;
        breadth = mvobj.breadth;
        std::cout<<"Move CTOR : \n";
        display();
    }  
    void display()
    {
        std::cout<<"Obj Address : "<<this<<"\t";
        std::cout<<"Length = "<<length <<"| Breadth = "<<breadth<<std::endl;
    }
};

int main()
{
    std::cout<<"Hello World\n";
    //Default CTOR
    Rectangle R1;
    R1.display(); //Rectangle::display(&R1);    => this=&R1

    //Parameterised CTOR
    Rectangle R2(3,5);   //Rectangle::Rectangle(&R2,3,5);

    //Copy CTOR
    Rectangle R3(R2);
    Rectangle R4 = R2;
  
    //Copy Assignment
    R1 = R3;

    //move CTOR
    Rectangle R5(std::move(R1));
    //Obj after Move 
    std::cout<<"Object R1 after move : \n";
    R1.display();

 

    return 0;
}
