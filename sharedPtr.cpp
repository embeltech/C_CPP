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
    Rectangle R1("R1",1,2);
    R1.print();
    //make_shared creates completely new object on heap and initializes with value of R1
    std::shared_ptr<Rectangle> sptr1 = std::make_shared<Rectangle>(R1);
    R1.set(3,4);
    R1.print();
    sptr1->print();
    std::cout<<"Reference count sptr1 : "<<sptr1.use_count()<<std::endl;
//-----------------------------------------------------------------------   
    auto sptr2 = std::shared_ptr<Rectangle>(new Rectangle ("R2",5,6));
    sptr2->print();
    std::cout<<"Reference count sptr2: "<<sptr2.use_count()<<std::endl;
    {
        auto sptr3=sptr2;
        std::cout<<"Reference count sptr2: "<<sptr2.use_count()<<std::endl;
        std::cout<<"Reference count sptr3: "<<sptr3.use_count()<<std::endl;
    }

    std::cout<<"Outside local block\n";
    std::cout<<"Reference count sptr2: "<<sptr2.use_count()<<std::endl;
//-----------------------------------------------------------------------  
    auto sptr4=sptr2;
    std::cout<<"Reference count sptr4: "<<sptr2.use_count()<<std::endl;
    sptr2.reset(); //reference count drops to 0 and pointer becomes null. Object is not deleted as sptr4 still points to object R2
    std::cout<<"sptr2.reset()\n";
    std::cout<<"Reference count sptr2: "<<sptr2.use_count()<<std::endl;
    if(sptr2)
    {
        std::cout<<"sptr2 not null\n";
    }
    else
    {
        std::cout<<"sptr2 null\n";
    }
  //-----------------------------------------------------------------------
    std::cout<<"Reference count sptr4: "<<sptr4.use_count()<<std::endl; //sptr4 still points to R2 object
    if(sptr4)
    {
        std::cout<<"Resetting sptr4. Last pointer to R2 so object will also get deleted.\n";
        sptr4.reset();
    }
  //-----------------------------------------------------------------------
    std::shared_ptr<Rectangle> sptr5(new Rectangle("R3",10,20));
    std::cout<<"Reference count sptr5: "<<sptr5.use_count()<<std::endl;
    sptr5->print();
    //resets sptr5. R4 will be created and sptr5 will point to R4.object R3 will get deleted as only pointer to R3 is getting reset
    sptr5.reset(new Rectangle("R4",10,20));
    sptr5->print();
//-----------------------------------------------------------------------
    std::cout<<"Main exiting\n";
    return 0;
}
