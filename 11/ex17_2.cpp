#include "ex17_2.h"
#include <memory>
#include <cstring>
#include <vector>
#include <iostream>

namespace ex17_2 {
using namespace std;
class Digit2
{
    friend ostream& operator<<(ostream& os,const Digit2& digit);
public:
    bool isOverflow;
    Digit2(){//初始化_digit
        _digit = new char[1];
        _digit[1] = '\0';
    }
    Digit2(const int n):isOverflow(false)
    {
        //初始化_digit
        _digit = new char[n+1];
        memset(_digit,'0',n);
        _digit[n] = '\0';
    }
    ~Digit2(){delete []_digit;}

    Digit2& operator ++()
    {
        isOverflow = false;
        int length = strlen(_digit);
        for(int index=length-1;index >=0;--index)
        {
            int number = _digit[index] - '0';
            if(index ==length-1)
                ++number;

            if(number>=10)
            {
                number -=10;
                if(index == 0)
                    isOverflow = true;
                else
                    ++_digit[index-1];

            }
            _digit[index] = number + '0';

        }

        return *this;
    }


    Digit2& operator =(const Digit2& rhs)
    {
        if(&rhs !=this)
        {
            delete []this->_digit;
            int length = strlen(rhs._digit);
            this->_digit = new char[length + 1];
            for(int i=0;i<=length;++i)
            {
                this->_digit[i] = rhs._digit[i];
            }
            this->isOverflow = rhs.isOverflow;
        }
        return *this;
    }

    Digit2 operator ++(int)
    {
        Digit2 preDigit;
        preDigit = *this;
        ++(*this);
        return preDigit;
    }
private:
    char* _digit;

};
ostream& operator<<(ostream& os,const Digit2& digit)
{
    int length = strlen(digit._digit);
    int index = 0;
    while(digit._digit[index] == '0') ++index;
    for(;index<length;++index)
        os<<digit._digit[index];
    return os;
}
void PrintOneToMaxOfNDigits_1(int n)
{
    if (n <= 0)
        return;
    Digit2 digit(n);
    while(!(++digit).isOverflow)
        cout << digit<<" ";
    cout  <<endl;
}
void printNum(char *num)
{
    unsigned index = 0;
    while(num[index]=='0')++index;
    if(index == strlen(num))
    {
        cout<<'0';
        return;
    }
    for(;num[index]!='\0';++index)
        cout << num[index];
}
class Digit
{
    friend ostream& operator<<(ostream& os,const Digit& digit);
public:
    Digit():length(0){_digit=std::move(vector<char>(0));}
    Digit(const int n):length(n){_digit=std::move(vector<char>(n,'0'));}

    vector<char> _digit;
    int length;

};
ostream& operator<<(ostream& os,const Digit& digit)
{
    int index = 0;
    while(digit._digit[index]=='0')++index;
    if(index == digit.length)
    {
        os<<'0';
        return os;
    }
    for(;index!=digit.length;++index)
        os<<digit._digit[index];
    return os;
}
void RecursionPrint1ToN(Digit& digit,int index,bool& isBeginning0)
{
    if(index == digit.length)
    {
        //第一次不打印，第一次是0
        if(isBeginning0)
        {
            isBeginning0 = false;
            return;
        }
        cout << digit<<" ";
        return;
    }
    for(int i=0;i<10;++i)
    {
        digit._digit[index] = '0'+i;
        RecursionPrint1ToN(digit,index+1,isBeginning0);
    }
}
void Print1ToMaxN(int n)
{
    if(n<=0)
        return;

    Digit digit(n);

    //第一次不打印出来，第一个数是0
    bool isBeginning0 = true;
    RecursionPrint1ToN(digit,0,isBeginning0);
}
void run()
{
    //PrintOneToMaxOfNDigits_1(4);
    Print1ToMaxN(8);
}
}
