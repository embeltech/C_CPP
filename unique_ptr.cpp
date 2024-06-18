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
    //make_unique creates completely new object on heap and initializes with value of R1
    std::unique_ptr<Rectangle> uptr1 = std::make_unique<Rectangle>(R1);
    R1.set(3,4);
    R1.print();
    uptr1->print();
//-----------------------------------------------------------------------  
    auto uptr2 = std::unique_ptr<Rectangle>(new Rectangle ("R2",5,6));
    uptr2->print();
    //auto sptr3=sptr2; error as unique pointer cannot be assigned to other variable
    auto uptr3 = std::move(uptr2);  //after moving sptr loses all ownership and becomes NULL
    uptr3->print();
    if(uptr2)
    {
        std::cout<<"uptr2 is not NULL\n";
    }
    else{
        std::cout<<"uptr2 is NULL\n";
    }
//----------------------------------------------------------------------- 
    uptr3.reset(); //pointer becomes null. Object is deleted as sptr3 is only pointer points to object R2
//-----------------------------------------------------------------------
    auto uptr4 = std::unique_ptr<Rectangle>(new Rectangle("R3",10,20));
    uptr4.release();
    if(uptr4)
    {
        std::cout<<"After Release uptr4. uptr4 is not NULL.\n";
    }
    else
    {
        std::cout<<"After uptr4.release() uptr4 is NULL.Object not deleted .The caller is responsible for cleaning up the object \n";
    }
  //-----------------------------------------------------------------------
    std::unique_ptr<Rectangle> uptr5(new Rectangle("R4",10,20));
    uptr5->print();
    //resets uptr5. R5 will be created and sptr5 will point to R5.object R4 will get deleted as only pointer to R3 is getting reset
    uptr5.reset(new Rectangle("R5",10,20));
    uptr5->print();
//-----------------------------------------------------------------------
    std::cout<<"Main exiting\n";
    return 0;
}
