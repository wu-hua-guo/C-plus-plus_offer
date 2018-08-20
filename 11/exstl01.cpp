#include "exstl01.h"
#include <iostream>
#include <vector>
#include <algorithm>
namespace  exstl01 {
using namespace std;
bool isBigger(const int& lhs,const int& rhs)
{
    return lhs > rhs;
}
template<typename T>
void printVec(std::vector<T>& vec)
{
    std::for_each(vec.begin(),vec.end(),[](const int& value){ std::cout<<value<<" ";});
}

template<typename T>
void printVec(T begin,T end)
{
    for(auto iter = begin;iter !=end;++iter)
        cout<<*iter<<" ";
    cout<<endl;
}

template<typename T>
void m_stableSort(T begin,T end)
{
    //递归的边界，如果只有一个元素就退出排序
    if(end - begin <= 1)
        return;
    auto sz = *begin;
    auto mid = std::stable_partition(begin,end,[sz](const int& value){ return value < sz;});

    if(mid > begin)
        m_stableSort(begin,mid);
    if(mid < end -1)
        m_stableSort(mid+1,end);
}


template<typename T>
void m_Sort(T begin,T end)
{
    //递归的边界，如果只有一个元素就退出排序
    if(end - begin <= 1)
        return;
    auto sz = *begin;

    auto mid = std::partition(begin,end,[sz](const int& value){ return value < sz;});

    //这里为什么需要交换mid和end-1这两个数？
    //如果序列是 1,2,3，那么partition之后还是1,2,3，就不需要交换
    //如果序列是 110,201,1,2，那么partition之后序列是，2,1,201,110，我们需要的中间值到尾部了，需要交换
    if(*mid != sz)
        std::swap(*mid,*(end-1));



    if(mid > begin)
        m_Sort(begin,mid);
    if(mid < end -1)
        m_Sort(mid+1,end);
}
int test()
{
    std::vector<int> numbers{33,12,51,88,98};
    std::cout<<"print orige numbers:\n";
    printVec(numbers.begin(),numbers.end());

    std::sort(numbers.begin(),numbers.end(),isBigger);

    std::cout<<"print after sort numbers:\n";
    printVec(numbers.begin(),numbers.end());

    return 0;
}
bool smallNumber(const int& value)
{
    return value<102;
}

int test02()
{
    std::vector<int> numbers{102,44,99,35,201,110,1,2,190};
    std::cout<<"print orige numbers:\n";
    printVec(numbers.begin(),numbers.end());

    auto mid =  std::stable_partition(numbers.begin(),numbers.end(),smallNumber);

    cout<<"mid:"<<*mid<<endl;
    std::cout<<"print after partition numbers:\n";
    printVec(numbers.begin(),numbers.end());

    return 0;

}
int test01()
{
    std::vector<int> numbers{34,12,99,10};
    int value=12;
    auto iter = std::find(numbers.begin(),numbers.end(),value);
    if(iter != numbers.end())
        std::cout<<"find:"<<*iter<<std::endl;
    else
        std::cout<<"12 is not in numbers\n";

    iter = std::find(numbers.begin(),numbers.end(),*(numbers.begin()+2));
    if(iter != numbers.end())
        std::cout<<"find:"<<*iter<<std::endl;
    else
        std::cout<<"is not in numbers\n";

    return 0;
}
int test03()
{
    auto f = [](){return "lambda";};
    std::cout<<f()<<std::endl;

}
int test06()
{
    std::vector<int> numbers{102,44,99,35,201,110,1,2};
    std::cout<<"print orige numbers:\n";
    printVec(numbers);
    std::cout<<std::endl;

    auto sz = *numbers.begin();

    std::stable_partition(numbers.begin(),numbers.end(),[sz](const int& value){ return value < sz;});
    printVec(numbers);
    std::cout<<std::endl;

    return 0;
}
int test07()
{
    std::vector<int> numbers{102,44,99,35,201,110,1,2};
    std::cout<<"print orige numbers:\n";
    printVec(numbers);
    std::cout<<std::endl;

    auto sz = *numbers.begin();

    std::partition(numbers.begin(),numbers.end(),[sz](const int& value){ return value < sz;});
    printVec(numbers);
    std::cout<<std::endl;


    return 0;
}
int test08()
{
    std::vector<int> numbers{102,44,99,35,201,110,1,2};
    std::cout<<"print orige numbers:\n";
    printVec(numbers);
    std::cout<<std::endl;

    m_stableSort(numbers.begin(),numbers.end());

    std::cout<<"print after m_stableSort numbers:\n";
    printVec(numbers);
    std::cout<<std::endl;


    return 0;
}
int test09()
{
    std::vector<int> numbers{102,44,99,35,201,110,1,2};
    std::cout<<"print orige numbers:\n";
    printVec(numbers.begin(),numbers.end());

    m_Sort(numbers.begin(),numbers.end());

    std::cout<<"print after m_Sort numbers:\n";
    printVec(numbers.begin(),numbers.end());


    return 0;
}
int run()
{

    test08();
    test09();

    return 0;
}
}
