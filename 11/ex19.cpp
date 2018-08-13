#include "ex19.h"
#include <cstdio>
#include <iostream>
#include <cstring>
namespace ex19{
using std::cout;
using std::endl;
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

// 面试题19：正则表达式匹配
// 题目：请实现一个函数用来匹配包含'.'和'*'的正则表达式。模式中的字符'.'
// 表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本题
// 中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"
// 和"ab*ac*a"匹配，但与"aa.a"及"ab*a"均不匹配。



bool matchCore(const char* str, const char* pattern);
bool myMatchCore(const char* str, const char* pattern);

bool myMatch(const char* str,const char* pattern)
{
    if(str==nullptr||pattern==nullptr)
        return false;

    return myMatchCore(str,pattern);
}
bool myMatchCore(const char* str, const char* pattern)
{
    if(*str == '\0' &&*pattern == '\0')
        return true;

    if(*(pattern+1) == '*')
    {
        if(*str == *pattern ||(*pattern =='.' && *str != '\0'))
        {
            // 继续留在有限状态机的当前状态，.*匹配[0,+）个字符，匹配下一个字符
            return  myMatchCore(str+1,pattern)||
                    // 略过一个'*',匹配0给字符
                    myMatchCore(str,pattern+2);
        }
        else
            return myMatchCore(str,pattern+2);
    }

    if(*str == *pattern ||(*pattern =='.' && *str != '\0'))
        return myMatchCore(str+1,pattern+1);

    return false;
}
//void test(const char* str,const char* pattern)
//{
//    cout << str <<" "<< pattern<<" ismatch:"<<myMatch(str,pattern)<<endl;
//}

bool match(const char* str, const char* pattern)
{
    if(str == nullptr || pattern == nullptr)
        return false;

    return matchCore(str, pattern);
}

bool matchCore(const char* str, const char* pattern)
{
    //字符串为空或者str与pattern都匹配结束
    if(*str == '\0' && *pattern == '\0')
        return true;

    //str没有结束，但是pattern结束，则匹配失败0
    if(*str != '\0' && *pattern == '\0')
        return false;

    //如果模式中下一个元素是'*'则，*是[0，+）的意思，可能匹配0个，或者很多个*tr
    if(*(pattern + 1) == '*')
    {
        //模式中第一个字符与字符串中第一个字符匹配
        if(*pattern == *str || (*pattern == '.' && *str != '\0'))
            // 进入有限状态机的下一个状态
            return //matchCore(str + 1, pattern + 2)||
                    // 继续留在有限状态机的当前状态
                    matchCore(str + 1, pattern)||
                    // 略过一个'*'
                    matchCore(str, pattern + 2);
        else
            // 略过一个'*'
            return matchCore(str, pattern + 2);
    }

    //如果模式中下一个元素不是'*'，则检验字符串当前一个字符与pattern当前字符是否相等
    if(*str == *pattern || (*pattern == '.' && *str != '\0'))
        return matchCore(str + 1, pattern + 1);

    return false;
}
// ====================测试代码====================
void Test(const char* testName, const char* string, const char* pattern, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(myMatch(string, pattern) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}
void test(const char* string,const char* pattern)
{
    cout <<"str:"<<string<<" pattern:"<<pattern;
    if(myMatch(string,pattern))
        cout<<" is match"<<endl;
    else
        cout<<" isn't match"<<endl;
}

int run()
{
    test( "", "");
    test( "", ".*");
    test( "", ".");
    test( "", "c*");
    test( "a", ".*");
    test("a", "a.");
    test("a", "");
    test("a", ".");
    test("a", "ab*");
    test("a", "ab*a");
    test("aa", "aa");
    test("aa", "a*");
    test("aa", ".*");
    test("aa", ".");
    test( "ab", ".*");
    test("ab", ".*");
    test("aaa", "aa*");
    test("aaa", "aa.a");
    test("aaa", "a.a");
    test("aaa", ".a");
    test("aaa", "a*a");
    test("aaa", "ab*a");
    test("aaa", "ab*ac*a");
    test("aaa", "ab*a*c*a");
    test("aaa", ".*");
    test("aab", "c*a*b");
    test("aaca", "ab*a*c*a");
    test("aaba", "ab*a*c*a");
    test("bbbba", ".*a*a");
    test("bcbbabab", ".*a*a");
    test("a", ".*a*a");
    test("aa", ".*a*a");
    return 0;
}


}
