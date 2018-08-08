#ifndef EX11_H
#define EX11_H
#include <iostream>
#include <vector>
#include <stdexcept>
using std::vector;
using std::cout;
using std::endl;
namespace ex11{

int MinOrder(vector<int>& numbers)
{
    int size = numbers.size();
    if(size == 1)
        return numbers[0];

    int result = numbers[0];
    for(int i=1;i<size;++i)
    {
        if(result>numbers[i])
            result = numbers[i];
    }
    return result;
}

int Min(vector<int> &numbers)
{
    if(numbers.empty())
        throw std::logic_error("Invalid Parameters!");

    if(numbers.size()==1)
        return numbers[0];
    vector<int>::iterator index1 = numbers.begin();
    auto index2 = numbers.end() - 1;
    auto midIndex = index1;

    while(*index1 >= *index2)
    {
        if(index2 - index1 == 1){
            midIndex = index2;
            break;
        }
        midIndex = index1 + (index2 - index1)/2;

        if(*index1 == *index2&& *index1 == *midIndex)
            return MinOrder(numbers);

        if(*midIndex >= *index1)
            index1 = midIndex;
        else if(*midIndex <= *index2)
            index2 = midIndex;

    }

    return *midIndex;

}

void test()
{
    vector<int> numbers{2,2,3,4,5};
    cout << Min(numbers)<<endl;

    numbers={3,4,5,6,2};
    cout << Min(numbers) <<endl;

    vector<int> numbers2{1,0,1,1,1};
    cout << Min(numbers2) << endl;

    int array1[] = {2,2,2,2,1};
    vector<int> numbers3{array1,array1+5};
    cout << Min(numbers3) <<endl;
}

void run()
{
    test();
}
}
#endif // EX11_H
