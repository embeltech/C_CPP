## Generic C++ Part
1. What is Vtable and Vptr how it works?
2. What is virtual destructor, why it is used?
    - virtual keyword required when base class pointer(bptr) stores derived class object and delete bptr is invoked.
    - destruction should happen in reverse order -> destroy derived part then destroy base part
    - if virtual keyword is not used and bptr is destroyed then only base DTOR will be called and derived class part will not be destroyed.
3. Why pure virtual fuction is used?
    - one or more pure virtual functions makes class abstract whose object creation is not possible.
    - to force derived classes to provide its body else derived class becomes abstract.
    - pure virtual function can have body. It cannot have body inline but should be given outside of class using scope resolution. 
    - Pure virtual function body can be called from derived class which implements it using base::pure_virtual_func().
4. Can we use virtual contructor?
    - No. At the time of constructing object Vtable and __vptr are not available.
5. Difference between pointer and refernce and why ref is used?
    - Memory location
      - Reference is just another name for memory location of variable so no additional memory space is used by referennce
      - Pointer is separate memory location which holds address of memory location of variable
    - Null Check
      - reference cannot be NULL as it has to be assigned value at the time of declaration or before using it so no segmentation fault.
      - pointers can be NULL
    - Reassignment
      - Whenever reassignment is needed prefer pointer else use reference as reassignment of reference to other variable is not possible.
6. Static key word in C++
    - Static Local Variables: Retain their value between function calls and have a lifetime till end of program.
    - Static Global Variables: Access is limited to the file in which they are declared. Need to use extern for use in other files.
    - Static Functions: Access is limited to the file in which they are declared. Need to use extern for use in other files.
    - Static Data Members: Shared by all instances of the class and exist independently of any class objects.
    - Static Member Functions: Can be called without an instance of the class (using class_name::static_func_name) and can only access static data members and other static member functions.
7. what compiler provides by default in C++?
    - default constructor, 
    - default copy constructor
    - default copy-assignment operator
    - default destructor
8. explicit keyword
    - if explicit is used for CTOR, copy CTOR, DTOR then compiler do not generate them by default.
    - No implicit type casting is done by compiler.
9. What is IPC? Name some of them.
    - shared memory (used by POSIX)
    - Message Queues (used by Mac)
    - Pipe
    - socket
    - remote procedural call RPC (windows uses local procedural call)
10. IPC synchronization
11. Design Patterns
    - Creational : Singleton, factory  (product - concrete product, product factory - concrete product factory)
    - Structural : Proxy              (real service, proxy service)
    - Behavioral : Observer pattern  (publisher, subscriber)
12. Storage Classes in CPP
    - auto: Default storage class for local variables. Scope : Local, Lifetime : till function call
    - register: Suggests Compiler to store the variable in a CPU register for faster access. Scope : Local, Lifetime : till function call
    - static: Retains value between function calls, limits scope to the file. Scope : Local, Lifetime : till end of program
    - extern: Declares a variable or function defined in another file. Scope : global, Lifetime : till end of program
    - mutable: Used for member variables of class whose objects are declared as constants. It Allows modification of member variables even in const objects.

----------------------------------------------------------------------------
## C++ 11
1. Type inference
    - auto - type infered from values assigned to variables.
    - decltype() - needs additinal information to infer type. Better for expressions.
2. nullptr
    - NULL defined as (void *) 0 in #include<stddef.h>
    - NULL implicitly typecasted to int x= NULL;
    - func(NULL) will create ambiguity to resolve to func(char * ptr) or func(int)
    - use nullptr for null pointers
3. Range-Based for Loops
4. explicit
5. Override and Final
    - override used at the end of class member function to ensure correct function is overriden in derived class
    - final keyword if used at the end of virtual function of base class, that function cannot be overridden in derived class
    - final keyword if used at the end of base class, that class cannot be inherited further.
6. Smart Pointers
    - list all member functions
        - shared_ptr : reset,use_count
        - unique_ptr : reset,release,std::move
        - weak_ptr : reset,expired,lock
    - implement your own version of shared_ptr, unique_ptr, weak_ptr
    - why auto_ptr removed in cpp17
7. Lambdas
8. std::function, bind
9. Initializer lists
10. Delegating constructors
11. Move Semantics
12. std::thread
13. Mutex, locks,condition variables
14. Future,promise
15. The constexpr keyword
    - It removes the function calls and evaluates the code/expressions in compile time.
    - should contain only one return statement
    - prefix increment (++v) was not allowed
16. Deleted and defaulted functions
17. Strongly-typed,scoped Enums
    - strongly typed : underlying datatype can be provided. enum class colours:char{red,green,blue}
    - strongly scoped : colours var = colours::red;

-------------------------------------------------------------------------------------------------------------------
## C++ 14 [Feature List](https://blogs.embarcadero.com/a-complete-guide-to-the-list-of-features-in-c-14/)
### New language features
1. variable templates
    - `template <class T> constexpr T e = T(2.718281828459045);`
    - `int x = e<int>; double d = e<double>;`
2. lambdas
    - generic lambda : use of auto in parameters datatype
    - lambda init-capture : initializing captured variable in capture clause. capture by move useful for unique_ptr
3. new/delete elision
4. relaxed restrictions on constexpr functions
    - multiple return statements allowed
    - prefix increment (++v) allowed
    - if else, switch , loops allowed
5. binary literals
    - provides a convenient way to represent a binary. int b1 = 0b00111011;
6. digit separators
    -  use of single quotes in numeric literals, making them easier to read.
    -  `int price = 1'000;`
7. return type deduction for functions
    - allows functions to deduce their return type automatically based on the type of their return
    - `auto add(int x, int y){return x+y;}`
8. aggregate classes with default non-static member initializers.
9. Standard user-defined literals
    - `auto str = "hello world"s; //auto deduces string`
    - `auto dur = 60s;            // auto deduces chrono::seconds`
10. Tuple addressing via type
    - `std::tuple<string, string, int> t("foo", "bar", 7);`
    - `int i = std::get<int>(t);`        

### New library features
11. std::make_unique
    - `auto ptr = std::make_unique<int>(5); std::cout<<*ptr;`
    - `auto arr = std::make_unique<int[]>(10); //int array of size 10`
    - arr[0] to arr[9]
12. std::shared_timed_mutex and std::shared_lock

----------------------------------------------------------
## C++ 17
1. Nested Namespaces
    ```
    namespace BMWgroup::Mini::plant {
    
        class vehicle {
        
        };
    
    }
    ```
   
3. Variable declaration in if and switch
    ```
    if(int x = getVal(); x == 25)
        std::cout<<"x is 25";
    else
        std::cout<<x;
    ```
    ```
    switch(Variable declaration ; variable)
    {
        // Cases
    }
    ```
5. if constexpr statement : The code inside the block which is not selected gets discarded during compilation.
    ```
    if constexpr (condition) {
        // Code executed only if condition is true at compile time
    } else {
        // Code executed only if condition is false at compile time
    }
    ```
7. Structured bindings
    ```
    std::map<std::string, std::string> MyMap{ 
            { "Key1", "Val1" }, 
            { "Key2", "Val2" }, 
            { "Key3", "Val3" } 
        }; 
    for(auto [key,val] : MyMap)
            std::cout<<key<<":"<<val<<std::endl;
    ```
9. Fold Expressions
10. Direct list initialization of enums

------------------------------------------------
TTL JV 1 interview

1.What Producto platform u used?
 HW arm chip AP PP
  SW Linux
2.For arm chip how build on your m/c for HW?
-  Cross complilation using Vmware and on server jenkins
2.How PP AA chips communicate ?
Dbus
3.How service carsh debugging take place?
coredump and logging
4.How to test if target maching is not availabel?
Simulation ,  
5.How to do developer testing for fuction you were written?
UTC, manually test, automation.
6.How to debug in production enviromrnt if logs are disable?
Via Diagnostic mode to get critical data from ECU clustuer?
7.How to ensure quality of code.
Use static code analyzer like Parasoft
Misra compilance
Valgrind - memory likes
8.Code review checklist
Is UTC doe?
Is Developer test done on simulation + HW
Is pear reviews doen with in team
All coding guideline followed
Misra compalnce
Static code parasof and valagring report available
Test reports and flow diag attached
Any impediance or viewers ?
9.What challagening problem you solved
??HMI perfromance issue
.Ledership experience to handle team?
https://www.geeksforgeeks.org/features-of-c17-with-examples/
https://www.codingame.com/playgrounds/2205/7-features-of-c17-that-will-simplify-your-code/introduction


