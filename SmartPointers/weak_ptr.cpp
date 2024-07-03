#include <iostream>
#include <memory> // For shared_ptr

class Rectangle{
    std::string strName;
    int iLength,iBreadth;
    public:
      Rectangle(std::string name, int x, int y):strName(name),iLength(x),iBreadth(y)
      {
          std::cout<<"Created Rectangle : "<<strName<<" ["<<iLength<<","<<iBreadth<<"]\n";
      }
      void print()
      {
          std::cout<<"Rectangle : "<<strName<<" ["<<iLength<<","<<iBreadth<<"]\n";
      }
      void set(int x, int y)
      {
        iLength=x;
        iBreadth=y;
      }
      ~Rectangle()
      {    
        std::cout<<"Object deleted : "<<strName<<std::endl;
      }

}; 

int main()
{
    std::cout<<"Hello World\n";
    //make_shared creates completely new object on heap and initializes with value of R1
    std::shared_ptr<Rectangle> sptr1 = std::make_shared<Rectangle>("R1",1,2);
    sptr1->print();
    std::cout<<"Reference count sptr1 : "<<sptr1.use_count()<<std::endl;
    
    std::weak_ptr<Rectangle> wptr1 = sptr1;
    // Weak ptr does not increase the reference count as it does not share ownership of object
    std::cout<<"Reference count wptr1 : "<<wptr1.use_count()<<std::endl;
    std::cout<<"Reference count sptr1 after weak ptr : "<<sptr1.use_count()<<std::endl;
    
    if(!wptr1.expired()) //checks if ownership has expired.
    {
        std::cout<<"Object still exist owned by original shared ptr\n";
        std::cout<<"Now deleting the object using sptr1\n";
        sptr1.reset();
        std::cout<<"wptr1.expired() : "<<(wptr1.expired() ? "True":"False")<<std::endl;
        std::cout<<"Reference count wptr1 : "<<wptr1.use_count()<<std::endl;
        std::cout<<"Reference count sptr1 : "<<sptr1.use_count()<<std::endl;
        
    }
    else
    {
        std::cout<<"Object does not exist\n";
    }
    
//-----------------------------------------------------------------------   
    auto sptr2 = std::shared_ptr<Rectangle>(new Rectangle ("R2",5,6));
    sptr2->print();
    std::cout<<"Reference count sptr2: "<<sptr2.use_count()<<std::endl;
    {
        std::weak_ptr<Rectangle> wptr2=sptr2;
        //wptr2->print(); gives error
        auto temp_sp = wptr2.lock(); //lock provides temporary ownership of object.Reference count also increase.
        temp_sp->print(); //to access data or call function lock() is mandatory.
        std::cout<<"Reference count temp_sp: "<<temp_sp.use_count()<<std::endl;
    
    }
    std::cout<<"Reference count sptr2 outside block: "<<sptr2.use_count()<<std::endl;
    
   
//-----------------------------------------------------------------------  
    std::weak_ptr<Rectangle> wptr3(sptr2);
    std::cout<<"Reference count before wptr reset : "<<wptr3.use_count()<<std::endl;
    wptr3.reset(); //reference count drops to 0 and pointer becomes null. Object is not deleted as sptr4 still points to object R2
    std::cout<<"wptr3.reset()\n";
    std::cout<<"Reference count after wptr3 reset: "<<wptr3.use_count()<<std::endl;
    if(!wptr3.expired())
    {
        std::cout<<"wptr3 not null\n";
    }
    else
    {
        std::cout<<"wptr3 null\n";
    }
 
    std::cout<<"Main exiting\n";
    return 0;
}
