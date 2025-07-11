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
    void display()
    {
        //std::cout<<"Obj Address : "<<this<<"\t";
        std::cout<<"Length = "<<length <<"| Breadth = "<<breadth<<std::endl;
    }
    void operator=(const Rectangle& rhs)
    {
        length = rhs.length;
        breadth = rhs.breadth;
        std::cout<<"operator= called : ";
    }
    
    Rectangle operator+(const Rectangle &rhs)
    {
        Rectangle temp;
        temp.length = length + rhs.length;
        temp.breadth = breadth + rhs.breadth;
        std::cout<<"operator+ called : ";
        return temp;
    }
    
    
    //overloading operator using friend function
    friend Rectangle operator-(const Rectangle &r1, const Rectangle &r2);
    friend std::ostream& operator<< (std::ostream &out, const Rectangle &rhs);
    friend std::istream& operator>> (std::istream &in,  Rectangle &r);
    
    Rectangle operator++()//preincrement 
    {
        std::cout<<"pre-increment operator++ called\n";
        length++;
        breadth++;
        return *this;
    }
    
    Rectangle operator++(int)//postincrement 
    {
        Rectangle temp = *this;
        std::cout<<"Post-increment operator++ called\n";
        length++;
        breadth++;
        return temp;
    }
    
    //functor
    Rectangle operator()(int mul)
    {
        std::cout <<"Functor called : ";
        Rectangle r;
        r.length = length * mul;
        r.breadth = breadth * mul;
        return r;
    }
    
};

Rectangle operator-(const Rectangle &r1, const Rectangle &r2)
{
    Rectangle temp;
    temp.length = r1.length - r2.length;
    temp.breadth = r1.breadth - r2.breadth;
    std::cout<<"Friend operator- called : "; 
    return temp;
}

std::ostream& operator<< (std::ostream &out, const Rectangle &rhs)
{
    std::cout<<"friend operator <<  called : ";
    out <<"Length = "<<rhs.length <<"||Breadth = "<<rhs.breadth<<std::endl;
    return out;
}
std::istream& operator>> (std::istream &in,  Rectangle &r)
{
    std::cout<<"Enter dimensions : \n";
    in >> r.length;
    in >> r.breadth;
    return in;
}


int main()
{
    std::cout<<"Hello World\n";
    //Parameterised CTOR
    Rectangle R1(3,5);
    //Default CTOR
    Rectangle R2;
  
    //Copy Assignment. operator= will be called
    R2 = R1;
    R2.display();
    
    Rectangle R3 = R1 + R2;
    R3.display();

    Rectangle R4 = R3 - R2;
    R4.display();
    
    std::cout<<R3<<std::endl;
    
    Rectangle R5;
    std::cin>>R5;
    R5.display();
    
    Rectangle x = R5++;
    std::cout<<R5;
    std::cout<<"x : "; x.display();
    x = ++R5;
    std::cout<<R5;
    std::cout<<"x : "; x.display();
    
    Rectangle R6 = R5(10);  //functor called.
    R6.display();

    return 0;
}
