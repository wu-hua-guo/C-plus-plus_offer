#include "ex15.h"
#include <iostream>
using std::cout;
using std::endl;
namespace ex15 {
int NumberOf1_1(int n)
{
    int count = 0;
    while(n)
    {
        if(n&1)
            ++count;
        n = n>>1;
    }
    return count;
}
int NumberOf1_2(int n)
{
    int count = 0;
    int flag = 1;
    while(flag)
    {
        if(n&flag)
            ++count;
        flag = flag<<1;
    }
    return count;
}

int NumberOf1_3(int n)
{
    int count = 0;
    while(n)
    {
        ++count;
        n = (n-1)&n;
    }
    return count;
}
void Test(int n,int result)
{
    cout << "n="<<n<<" result:"<<result<<endl;
    //cout <<NumberOf1_1(n)<<" ";
    cout <<NumberOf1_2(n)<<" "<<NumberOf1_3(n)<<endl;
    cout <<"-----------"<<endl;
}

void run()
{
    // 输入0，期待的输出是0
    Test(0, 0);

    // 输入1，期待的输出是1
    Test(1, 1);

    // 输入10，期待的输出是2
    Test(10, 2);

    // 输入0x7FFFFFFF，期待的输出是31
    Test(0x7FFFFFFF, 31);

    // 输入0xFFFFFFFF（负数），期待的输出是32
    Test(0xFFFFFFFF, 32);

    // 输入0x80000000（负数），期待的输出是1
    Test(0x80000000, 1);
}
}
