#include "ex18_3.h"
#include <iostream>
namespace ex18_3{
using namespace std;
class ListNode
{

    friend ostream& operator <<(ostream&os,const ListNode& myListNode);
public:

    void clear()
    {
        if(this ==nullptr)
            return;

        ListNode* head = this;
        ListNode* pNext = nullptr;
        while(head!=nullptr)
        {
            pNext = head->pNext;
            delete head;
            head = pNext;
        }
    }

    bool removeNode(ListNode*& node)
    {
        if(!node||!this)
            return false;
        if(node->pNext !=nullptr )
        {
            ListNode* pNext = node->pNext;
            node->_value = pNext->_value;
            node->pNext = pNext->pNext;
            delete pNext;
            pNext = nullptr;
            return true;
        }
        else if(this == node)
        {
            delete node;
            node = nullptr;
            //this = nullptr;
            return true;
        }
        //删除的node在尾部或者不在
        else
        {

            ListNode* pNode = this;
            while(pNode->pNext != node && pNode !=nullptr)
            {
                pNode = pNode->pNext;
            }
            //删除节点是否在尾部
            if(pNode!=nullptr)
            {
                pNode->pNext =nullptr;
                delete node;
                node = nullptr;
                return true;
            }
            return false;
        }

    }

    ListNode():_value(-1),pNext(nullptr){}
    ListNode(int value):_value(value),pNext(nullptr){}
    int _value;
    ListNode * pNext;

};
ostream& operator <<(ostream&os,ListNode& head)
{
    ListNode* node = &head;
    if(node == nullptr)
        return os;
    while(node->pNext!=nullptr)
    {
        os<<node->_value<<" ";
        node = node->pNext;
    }
    os<<node->_value;
    return os;
}

void change(ListNode* myListNode,int value)
{
    myListNode->_value = value;
}
int run()
{
    ListNode* number1 = new ListNode(1);
    ListNode* number2 = new ListNode(2);
    ListNode* number3 = new ListNode(3);
    ListNode* number4 = new ListNode(4);
    number3->pNext = number4;


    cout <<"delete number1 in number1 before:"<<*number1<<endl;
    number1->removeNode(number1);
    cout <<"delete number1 in number1 after:"<<*number1<<endl;

    number1->removeNode(number2);
    cout <<"delete number2 in number1 after:"<<*number1<<endl;



    number3->removeNode(number3);
    cout <<"delete number3 in number3 after:"<<*number3<<endl;

    //cout <<*number4 <<endl;
    return 0;
}
}
