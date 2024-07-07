#include <iostream>
#include <bitset>
int main()
{
    std::bitset<16> b16 = 0x0A0A;
    std::bitset<8> b8 = 0b0000'1010;    //cpp 14 : binary literals 0b with digit seperators '
    std::cout<<"b16 : "<<b16<<std::endl;
    std::cout<<"b8 : "<<b8<<std::endl;
    
    for(unsigned short i = 0; i < b8.size(); i++)
        if(b8.test(i))  //test if bit number i is set => true
           b8.reset(i);             //reset the bit if already set
           //b8.set(i,0); 
        else
            b8.set(i,1);            //set the bit if already reset
            //b8.set(i);
            
    std::cout<<"b8 after toggle : "<<b8<<std::endl;
    return 0;
}
