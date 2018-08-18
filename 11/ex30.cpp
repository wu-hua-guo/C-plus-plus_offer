#include "ex30.h"
#include <iostream>
using std::cout;
using std::endl;
namespace ex30 {

void Test(const char* testName,const StackWithMin<int>& stack,int expected)
{
    if(testName != nullptr)
        cout<<testName<<" begins: ";

    if(stack.min() == expected)
        cout<<"Passed."<<endl;
    else
        cout<<"Failed."<<endl;
}

int run()
{
    StackWithMin<int> stack;

    stack.push(3);

    stack.pop();
    stack.pop();

    stack.pop();
    stack.pop();

    return 0;
}


}
