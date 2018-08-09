#include "ex17_1.h"
#include <memory>
#include <cstring>
#include <vector>
#include <iostream>
namespace  ex17_1 {

using  namespace std;
class Digit
{
    friend ostream& operator<<(ostream& os,const Digit& digit);
public:
    //是否溢出判断
    bool isOverflow;
    Digit(){}
    Digit(const int n):isOverflow(false){_digit = std::move(vector<char>(n,'0'));}

    Digit& operator ++()
    {
        isOverflow = false;
        //使用反向迭代器进行模拟计算
        auto rbegin_iter = _digit.rbegin(),rend_iter = _digit.rend();
        for(auto reiter = rbegin_iter;reiter!=rend_iter;++reiter)
        {
            int number = *reiter - '0' ;
            if(reiter == rbegin_iter)
                ++number;
            if(number >=10)
            {
                number -=10;
                if( reiter+1 != rend_iter)
                    *(reiter+1) +=1;
                else
                    isOverflow = true;
            }
            *reiter = number + '0';
        }
        return *this;
    }
    Digit& operator =(const Digit& rhs)
    {
        this->_digit = rhs._digit;
        this->isOverflow = rhs.isOverflow;
        return *this;
    }

    Digit operator ++(int)
    {
        Digit preDigit;
        preDigit = *this;
        ++(*this);
        return preDigit;
    }
private:
    vector<char> _digit;

};
//输出字符串vector<char> _digit
ostream& operator<<(ostream& os,const Digit& digit)
{
    int length = digit._digit.size();
    int index = 0;
    while(digit._digit[index]=='0') ++index;
    for(;index<length;++index)
        os<<digit._digit[index];
    return os;
}

void PrintOneToMaxOfNDigits_1(int n)
{
    if (n <= 0)
        return;

    Digit digit(n);
    while(!(++digit).isOverflow)
    {
        cout << digit<<" ";
    }
    cout <<endl;
}
void run()
{
    PrintOneToMaxOfNDigits_1(3);
}
}
