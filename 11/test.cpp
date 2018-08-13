#include "test.h"
#include "ex11.h"
#include "ex12.h"
#include "ex13.h"
#include "ex13.h"
#include "ex14.h"
#include "ex15.h"
#include "ex16.h"
#include "ex17.h"
#include "ex17_1.h"
#include "ex17_2.h"
#include "ex18_1.h"
#include "ex18_2.h"
#include "ex18_3.h"
#include "ex19.h"
#include "ex20.h"
#include "ex21.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
bool max(const int& lhs,const int& rhs)
{
    if(lhs>rhs)
        return true;
    else
        return false;
}

Test::Test()
{
//    vector<int> iVec = {5,4,3,2,1};
//    sort(iVec.begin(),iVec.end());
//    //sort()
//    for_each(iVec.begin(),iVec.end(),[](const int& value){cout<<value<<" ";});
}
void swap(int &lhs,int& rhs)
{
    int temp = lhs;
    lhs = rhs;
    rhs = temp;
}

int partion(vector<int>& iVec,int start,int end)
{
    int small = start-1;
    for(int index = start;index < end;++index)
    {
        if(iVec[index] < iVec[end])
        {
            ++small;
            if(index !=small)
                swap(iVec[index],iVec[small]);
        }
    }
    ++small;
    swap(iVec[small],iVec[end]);

    return small;
}

void quickSort(vector<int>& iVec,int start,int end)
{
    if(start == end)
        return;

    int mid = partion(iVec,0,end);
    if(start < mid)
        quickSort(iVec,start,mid-1);

    if(mid < end)
        quickSort(iVec,mid+1,end);
}
void test()
{
    vector<int> iVec{4,3,2,4,1,5};
    for_each(iVec.begin(),iVec.end(),[](const int& value){cout<<value<<" ";});
    cout << endl;
    quickSort(iVec,0,iVec.size()-1);
    for_each(iVec.begin(),iVec.end(),[](const int& value){cout<<value<<" ";});
}

void Test::run()
{

    ex21::run();
}
