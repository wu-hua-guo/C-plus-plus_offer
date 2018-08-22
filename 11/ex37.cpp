#include "ex37.h"
#include <cstdio>
#include "Utilities\BinaryTree.h"


#include <cmath>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
namespace ex37 {
/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// 《剑指Offer——名企面试官精讲典型编程题》代码
// 作者：何海涛
//==================================================================

// 面试题37：序列化二叉树
// 题目：请实现两个函数，分别用来序列化和反序列化二叉树。


void printTree(const BinaryTreeNode* pRoot, ostream& stream)
{
    if(pRoot == nullptr)
    {
        stream<<"$,";
        return;
    }
    stream<<pRoot->m_nValue<<',';
    printTree(pRoot->m_pLeft,stream);
    printTree(pRoot->m_pRight,stream);
}


void Serialize(const BinaryTreeNode* pRoot, ostream& stream)
{
    if(pRoot == nullptr)
    {
        stream << "$,";
        return;
    }

    stream << pRoot->m_nValue << ',';
    Serialize(pRoot->m_pLeft, stream);
    Serialize(pRoot->m_pRight, stream);
}
bool ReadStream(istream& stream, int& number)
{
    if(stream.eof())
        return false;

    char buffer[32]{'\0'};
    int i=0;
    char ch;
    while(stream>>ch && ch !=',')
    {
        buffer[i++] = ch;
    }
    bool isNumeric = false;

    if(i > 0&& buffer[0] !='$')
    {
        number = atoi(buffer);
        isNumeric = true;
    }
    return isNumeric;
}

bool ReadStream_1(istream& stream, int* number)
{
    if(stream.eof())
        return false;

    char buffer[32];
    buffer[0] = '\0';

    char ch;
    stream >> ch;
    int i = 0;
    while(!stream.eof() && ch != ',')
    {
        buffer[i++] = ch;
        stream >> ch;
    }

    bool isNumeric = false;
    if(i > 0 && buffer[0] != '$')
    {
        *number = atoi(buffer);
        isNumeric = true;
    }

    return isNumeric;
}

void Deserialize(BinaryTreeNode*& pRoot, istream& stream)
{
    int number;
    if(ReadStream(stream, number))
    {
        pRoot = new BinaryTreeNode();
        pRoot->m_nValue = number;
        pRoot->m_pLeft = nullptr;
        pRoot->m_pRight = nullptr;

        Deserialize(pRoot->m_pLeft,stream);
        Deserialize(pRoot->m_pRight,stream);
    }
}
void Deserialize_1(BinaryTreeNode** pRoot, istream& stream)
{
    int number;
    if(ReadStream_1(stream, &number))
    {
        *pRoot = new BinaryTreeNode();
        (*pRoot)->m_nValue = number;
        (*pRoot)->m_pLeft = nullptr;
        (*pRoot)->m_pRight = nullptr;

        Deserialize_1(&((*pRoot)->m_pLeft), stream);
        Deserialize_1(&((*pRoot)->m_pRight), stream);
    }
}

// ==================== Test Code ====================
bool isSameTree(const BinaryTreeNode* pRoot1, const BinaryTreeNode* pRoot2)
{
    if(pRoot1 == nullptr && pRoot2 == nullptr)
        return true;

    if(pRoot1 == nullptr || pRoot2 == nullptr)
        return false;

    if(pRoot1->m_nValue != pRoot2->m_nValue)
        return false;

    return isSameTree(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
            isSameTree(pRoot1->m_pRight, pRoot2->m_pRight);
}
void Test_1(const char* testName, const BinaryTreeNode* pRoot)
{
    if(testName != nullptr)
        cout<<testName<<" begins: \n";

    PrintTree(pRoot);
}

void Test(const char* testName, const BinaryTreeNode* pRoot)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    ex37::printTree(pRoot,cout);
    cout<<endl;

    char* fileName = "test.txt";
    ofstream fileOut;
    fileOut.open(fileName);

    Serialize(pRoot, fileOut);
    fileOut.close();

    // print the serialized file
    ifstream fileIn1;
    char ch;
    fileIn1.open(fileName);
    while(fileIn1>>ch)
    {
        cout << ch;
    }
    fileIn1.close();
    cout << endl;

    ifstream fileIn2;
    fileIn2.open(fileName);
    BinaryTreeNode* pNewRoot = nullptr;
    Deserialize(pNewRoot, fileIn2);
    fileIn2.close();

    printTree(pNewRoot,cout);
    cout<<endl;

    if(isSameTree(pRoot, pNewRoot))
        printf("The deserialized tree is same as the oritinal tree.\n\n");
    else
        printf("The deserialized tree is NOT same as the oritinal tree.\n\n");

    DestroyTree(pNewRoot);
}

//            8
//        6      10
//       5 7    9  11
void Test1()
{
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

    ConnectTreeNodes(pNode8, pNode6, pNode10);
    ConnectTreeNodes(pNode6, pNode5, pNode7);
    ConnectTreeNodes(pNode10, pNode9, pNode11);

    Test("Test1", pNode8);

    DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test2()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode3, nullptr);
    ConnectTreeNodes(pNode3, pNode2, nullptr);

    Test("Test2", pNode5);

    DestroyTree(pNode5);
}

//        5
//         4
//          3
//           2
void Test3()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, nullptr, pNode4);
    ConnectTreeNodes(pNode4, nullptr, pNode3);
    ConnectTreeNodes(pNode3, nullptr, pNode2);

    Test("Test3", pNode5);

    DestroyTree(pNode5);
}

void Test4()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

    Test("Test4", pNode5);

    DestroyTree(pNode5);
}

void Test5()
{
    Test("Test5", nullptr);
}

//        5
//         5
//          5
//         5
//        5
//       5 5
//      5   5
void Test6()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode61 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode62 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode71 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode72 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode1, nullptr, pNode2);
    ConnectTreeNodes(pNode2, nullptr, pNode3);
    ConnectTreeNodes(pNode3, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode5, nullptr);
    ConnectTreeNodes(pNode5, pNode61, pNode62);
    ConnectTreeNodes(pNode61, pNode71, nullptr);
    ConnectTreeNodes(pNode62, nullptr, pNode72);

    Test("Test6", pNode1);

    DestroyTree(pNode1);
}
int test01()
{

    char buffer[32]{'\0'};
    //buffer[0] = '\0';

    int i=0;
    istringstream iss("123");
    char ch;
    while(iss>>ch)
    {
        buffer[i++]=ch;
    }
    string str(buffer);
    cout<<"str:"<<str<<endl;
    int number = atoi(buffer);
    cout<<"number:"<<number<<endl;

    return 0;

}
bool isShuixian(int numbers)
{
    if(numbers<100||numbers>999)
        return false;

    int ge = numbers%10;
    int shi = numbers/10%10;
    int bai = numbers/100;

    int sum = (int)pow(ge,3)+(int)pow(shi,3)+(int)pow(bai,3);
    return sum == numbers;
}
int test02()
{
    int count = 0;
    for(int i=100;i<=999;++i)
    {
        if(isShuixian(i))
        {
            cout<<i<<endl;
            ++count;
        }
    }
    cout<<count<<endl;
    return 0;
}
int test03()
{
    istringstream iss;
    iss.str("hi iss");
    string str;
    while(iss>>str)
        cout<<str<<endl;

    istringstream iss2("hi iss2");
    while (iss2>>str) {
        cout<<str<<endl;
    }
    return 0;
}
int test04()
{
    ostringstream oss;
    istringstream iss;
    iss.str("hi iss");
    string str;
    while(iss>>str)
        oss<<str<<endl;

    istringstream iss2("hi iss2");
    while (iss2>>str) {
        oss<<str<<endl;
    }
    cout<<oss.str();
    return 0;
}

int test05()
{
    stringstream sstr;
    int number = 999;
    string strNumber;
    sstr<<number;
    sstr>>strNumber;
    cout<<"strNumber:"<<strNumber<<endl;

    sstr.clear();
    string str("hi,xiaoming");
    char cstr[30];
    sstr<<str;
    sstr>>cstr;
    cout<<cstr<<endl;

    sstr.clear();
    char numbers[30]{'\0'};
    sstr<<243;
    sstr>>numbers;
    cout<<numbers<<endl;
    return 0;
}

bool write_ofstream(ofstream& ofs)
{
    //文件输出流是否打开
    if(!ofs.is_open())
        return false;
    ostringstream ostr;
    char* buffer="12345";
    for(int i=0;i<5;++i)
        ostr<<buffer<<'\n';

    ofs<<ostr.str();
    return true;
}
bool read_ifstream(ifstream& ifs)
{
    if(!ifs.is_open())
        return false;

    ostringstream ostr;
    int count = 0;
    char buffer[100];
    while (ifs.getline(buffer,100))
    {
        ostr <<++count<<":"<< buffer << endl;
    }
    cout<<ostr.str();
    return true;

}
int test06()
{
    ofstream ofs("test_fstream.txt",fstream::out);
    if(write_ofstream(ofs))
        cout<<"write success\n";
    else
        cout<<"write fail\n";
    ofs.close();

    ifstream ifs("test_fstream.txt",fstream::in);
    if(read_ifstream(ifs))
        cout<<"read success\n";
    else
        cout<<"read fail";

    return 0;
}
int test07()
{
    cout<<"fstream:\n";
    fstream fs("test_fstream.txt",fstream::in|fstream::out|fstream::app);

    fs<<"hello";
    //定位到尾部
    fs.seekg(0,fs.end);
    int length = fs.tellg();
    cout<<"length:"<<length<<endl;
    //定位到开头
    fs.seekg(0,fs.beg);

    char buffer[100];
    int count = 0;
    while(fs.getline(buffer,100))
        cout<<++count<<":"<<buffer<<endl;


    fs.close();
    return 0;
}

int test08()
{
    ifstream ifs;
    ifs.open("test.txt",fstream::in);

    char c;
    while(!ifs.eof())
    {
        ifs>>c;
        cout<<c;
    }
    return 0;
}
int test09()
{
    ifstream ifs;
    ifs.open("test.txt",fstream::in);

    char c;
    while(ifs>>c)
    {
        cout<<c;
    }
    return 0;
}
int run()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

//    test06();
//    test07();

//    test09();
    return 0;
}

}
