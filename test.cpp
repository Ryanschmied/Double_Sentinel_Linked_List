#include <iostream>
#include "Double_sentinel_list.h"

// Every C++ Project in Visual Studio and other IDEs can only have one file with a main() function.
// Thus, if you want this to compile, you must change the name to 'main()' and change the name of
// the 'main()' function in the driver to something else.
int main() {
    Double_sentinel_list<int> list;
    
    
     std::cout << "The list should be empty (1): " << list.empty() << std::endl;
     std::cout << "The size should be 0: " << list.size() << std::endl;
     std::cout << "The next pointer of begin should be the null pointer: " << list.begin()->next() << std::endl;
     std::cout << "The begin should equal end: " << (list.begin() == list.end()) << std::endl;
     
     list.push_front( 5 );
     list.push_back(7);
     
     std::cout << "The value of the node returned by begin should be 5: " << list.begin()->value() << std::endl;
     std::cout << "The value of the front should be 5: " << list.front() << std::endl;
     std::cout << "The value of the node returned by rbegin should be 7: " << list.rbegin()->value() << std::endl;
     std::cout << "The value of the back should be 7: " << list.back() << std::endl;
     std::cout << "The size should be 2: " << list.size() << std::endl;
     std::cout << "Should be an address: " << list.find(5) << std::endl;
     std::cout << "Should be 1: " << list.count(5) << std::endl;
     
     list.pop_front();
     
     std::cout << "The size should be 1: " << list.size() << std::endl;
     std::cout << "The value of the front should be 7: " << list.front() << std::endl;

    
    
    
    return 0;
}
