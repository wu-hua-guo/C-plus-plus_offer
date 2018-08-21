#include "exstl02.h"
#include <iostream>
#include <memory>
#include <list>
namespace exstl02 {
class m_string
{
    friend ostream& operator <<(ostream& os,const m_string& _string);
public:
    m_string(){str="";cout<<"creat m_string \n";}
    m_string(string s):str(s)
    {
        cout<<"creat m_string :"<<str<<endl;
    }
    ~m_string()
    {
        cout<<"delete m_string:"<<str<<endl;
    }
    string& getStr()
    {
        return str;
    }
    void setStr(string s)
    {
        str = s;
    }
    void print()
    {
        cout<<str<<endl;
    }
private:
    string str;
};
ostream& operator <<(ostream& os,const m_string& _string)
{
    os<<_string.str;
    return os;
}

int test01()
{
    shared_ptr<string> p1;
    shared_ptr<list<int>> p2;

    if(p1&& p1->empty())
        *p1 = "hi";

    shared_ptr<int> p3 = make_shared<int>(43);
    cout<<*p3<<endl;

    shared_ptr<string> p4 = make_shared<std::string>(10,'9');

    cout<<*p4<<endl;
    cout<<p1<<endl;
    return 0;
}
int test02()
{
    auto_ptr<m_string> pString(new m_string("m_string"));
    pString->setStr("hi ");
    cout<<*pString<<endl;
    pString.get()->print();
    pString->getStr() += "xiaoming !";
    cout<<*pString<<endl;
    pString.reset(new m_string("m_string"));
    cout<<*pString<<endl;
}
int test03()
{
    auto_ptr<m_string> p1(new m_string("hi"));
    auto_ptr<m_string> p2(new m_string("xiaoming"));
    p2 = p1;
    cout<<*p2<<endl;
    if(p1.get() == NULL)cout<<"p1 = NULL\n";
    return 0;
}
int test04()
{
    auto_ptr<m_string> p1(new m_string("123"));
    //p1.reset();
    p1.release();
    return 0;
}


int test06()
{
    shared_ptr<m_string> pm_string(new m_string("123"));
    shared_ptr<m_string> pm_string2(new m_string("456"));
    cout<<pm_string2->getStr()<<endl;
    cout<<pm_string2.use_count()<<endl;
    pm_string = pm_string2;//"456"引用次数加1，“123”销毁
    pm_string->print();
    cout<<pm_string2.use_count()<<endl;//2
    cout<<pm_string.use_count()<<endl;//2
    pm_string.reset();
    pm_string2.reset();//此时“456”销毁
    cout<<"done !\n";
    return  0;
}
int test07()
{
    shared_ptr<m_string> p1(new m_string("p1"));
    shared_ptr<m_string> p2 = make_shared<m_string>("p2");
    auto p3 = make_shared<m_string>("p3");
    auto p4 = p3;
    auto p5 = make_shared<pair<m_string,m_string>>( m_string("p5_1"), m_string("p5_2"));

    cout<<*p1<<":"<<p1.use_count()<< endl;
    cout<<*p2<<":"<<p2.use_count()<< endl;
    cout<<*p3<<":"<<p3.use_count()<< endl;
    cout<<*p4<<":"<<p4.use_count()<< endl;
    cout<<p5->first<<":"<<p5->second<<":"<<p5.use_count()<< endl;
    return  0;
}
int test08()
{
    std::shared_ptr<m_string> p1;
    std::shared_ptr<m_string> p2 (new m_string("p2"));

    //    cout<<"*p1： "<<*p1<<endl;

    //p1一开始是空的，现在使p1也指向p2的对象，这个时候，因为有两个智能指针指向同一个对象
    //使用shared_ptr类的计数器为2.
    p1 = p2;                          // copy

    cout<<"*p1: "<<*p1<<" "<<p1.use_count()<<endl;
    cout<<"*p2: "<<*p2<<" "<<p2.use_count()<<endl;
    cout<<endl;
    //cout<<"*p2: "<<*p2<<endl;

    //p2指向另外一个对象，这之前对象的计数器减1，即p1的计数器为1
    //p2因为指向一个新的对象，所以计数器也是为1
    p2 = std::make_shared<m_string> ("p2_1");   // move
    cout<<"*p1: "<<*p1<<" "<<p1.use_count()<<endl;
    cout<<"*p2: "<<*p2<<" "<<p2.use_count()<<endl;
    cout<<endl;

    //p1指向另外一个对象，这之前对象的计数器减1，这个时候，之前对象的计数器减少为1，所以调用m_string的解析函数，释放内存
    //p1因为指向一个新的对象，所以计数器也是为1
    std::unique_ptr<m_string> unique (new m_string("p3_unique"));
    p1 = std::move(unique);            // move from unique_ptr

    cout<<"*p1: "<<*p1<<" "<<p1.use_count()<<endl;
    cout<<"*p2: "<<*p2<<" "<<p2.use_count()<<endl;
    cout<<endl;
    return  0;
}
int test09()
{
    shared_ptr<m_string> p1 = make_shared<m_string>("p1");
    shared_ptr<m_string> p2 = make_shared<m_string>("p2");
    cout<<"*p1: "<<*p1<<" "<<p1.use_count()<<endl;
    cout<<"*p2: "<<*p2<<" "<<p2.use_count()<<endl;
    p1.swap(p2);
    cout<<"*p1: "<<*p1<<" "<<p1.use_count()<<endl;
    cout<<"*p2: "<<*p2<<" "<<p2.use_count()<<endl;
    return  0;

}
unique_ptr<m_string> fun()
{
    return unique_ptr<m_string>(new m_string("789"));
}
int test10()
{
    unique_ptr<m_string> p1(new m_string("p1"));
    //将所有权从p1（p1指向的m_string对象)转移给p2,release将p1制空
    unique_ptr<m_string> p2(p1.release());
    if(p1 == nullptr)
        cout<<"p1 is nullptr"<<endl;

    cout<<"*p2:"<<*p2<<endl;
    //对p2中的str重新复制成"p2"
    p2->setStr("p2");
    cout<<"*p2:"<<*p2<<endl;
    cout<<"------------\n";

    unique_ptr<m_string> p3(new m_string("p3"));
    //p2使用成员函数reset()先释放p2原来指向对象的内存
    p2.reset(p3.release());
    cout<<"*p2:"<<*p2<<endl;
    cout<<"------------\n";

    //不能直接使用p2.release(),p2不会释放内存，会丢失了指针， 需要一个指针来接管这个内存管理权，
    auto p = p2.release();
    cout<<"*p:"<<*p<<endl;
    delete p;
    cout<<"------------\n";



    unique_ptr<m_string> p4(new m_string("p4"));
    unique_ptr<m_string> p5(new m_string("p5"));
    //不能使用p4 = p5;
    //不能使用 p5 = p4.release();
    p5 = std::move(p4);
    if(p4 == nullptr)
        cout<<"p4 is nullptr"<<endl;
    cout<<"*p5:"<<*p5<<endl;
    cout<<"------------\n";

    //unique_ptr类的成员函数swap
    unique_ptr<m_string> p6(new m_string("p6"));
    unique_ptr<m_string> p7(new m_string("p7"));
    p6.swap(p7);
    cout<<"*p6:"<<*p6<<endl;
    cout<<"*p7:"<<*p7<<endl;
    cout<<"------------\n";

    //判断是否为空
    std::unique_ptr<m_string> p8;
    std::unique_ptr<m_string> p9 (new m_string("p9"));

    if (p8) std::cout << "p8 points to " << *p8 << '\n';
    else std::cout << "p8 is empty\n";

    if (p9) std::cout << "p9 points to " << *p9 << '\n';
    else std::cout << "p9 is empty\n";
    cout<<"------------\n";

    return  0;

}
int test11()
{
    std::shared_ptr<m_string> sp (new m_string("sp"));

    std::weak_ptr<m_string> wp1;
    std::weak_ptr<m_string> wp2 (wp1);
    std::weak_ptr<m_string> wp3 (sp);

    std::cout << "use_count:\n";
    std::cout << "wp1: " << wp1.use_count() << '\n';
    std::cout << "wp2: " << wp2.use_count() << '\n';
    std::cout << "wp3: " << wp3.use_count() << '\n';
    return 0;
}
class B;
class A
{
public:
    shared_ptr<B> _pb;
    ~A(){cout<<"delete A\n";}
};
class B
{
public:
    shared_ptr<A> _pa;
    ~B(){cout<<"delete B\n";}
};


int test12()
{
    shared_ptr<A> pa= make_shared<A>();
    shared_ptr<B> pb = make_shared<B>();

    pa->_pb = pb;
    pb->_pa = pa;
    cout<<pa.use_count()<<endl;
    cout<<pb.use_count()<<endl;
    return 0;
}

class B_2;
class A_2
{
public:
    shared_ptr<B_2> _pb;
    ~A_2(){cout<<"delete A_2\n";}
};
class B_2
{
public:
    weak_ptr<A_2> _pa;
    ~B_2(){cout<<"delete B_2\n";}
};
int test13()
{

    shared_ptr<A_2> pa= make_shared<A_2>();
    shared_ptr<B_2> pb = make_shared<B_2>();

    pa->_pb = pb;
    pb->_pa = pa;
    cout<<pa.use_count()<<endl;
    cout<<pb.use_count()<<endl;
    return 0;
}
int run()
{
    //m_string03();
    test12();
    cout<<"------------\n";
    test13();
    cout<<"------------\n";
    return 0;
}
}
