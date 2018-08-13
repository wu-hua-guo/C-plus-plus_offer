#include "ex18_a.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
namespace ex18_a
{

bool max(const int& lhs,const int& rhs)
{
    if(lhs>rhs)
        return true;
    else
        return false;
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

void quickSortCore(vector<int>& iVec,int start,int end)
{
    if(start == end)
        return;

    int mid = partion(iVec,0,end);
    if(start < mid)
        quickSortCore(iVec,start,mid-1);

    if(mid < end)
        quickSortCore(iVec,mid+1,end);
}
void quickSort(vector<int>& iVec)
{
    if(iVec.size()<=1)
        return;
    quickSortCore(iVec,0,iVec.size()-1);
}

int run()
{
    vector<int> iVec{4,3,2,4,1,5};
    for_each(iVec.begin(),iVec.end(),[](const int& value){cout<<value<<" ";});
    cout << endl;
    quickSort(iVec);
    for_each(iVec.begin(),iVec.end(),[](const int& value){cout<<value<<" ";});
}
}
