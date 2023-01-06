#include <iostream>
#include <string>
#include "util/endian.hpp"
#include "serial/single_include.hpp"

#define __test_templateExistence 0
#if __test_templateExistence
#include <vector>
template <typename E>
void foo(std::vector<E> &v) {}
#include <unordered_set>
template <typename E>
void foo(std::unordered_set<E> &s)
{
}
CheckFunctionExistence_withParam(foo)
#endif

#define __test_templateSplit 0
#if __test_templateSplit
#include <vector>
    template <typename E>
    void foo(std::vector<E> &v); // declare
template <typename E>
void foo(std::vector<E> &v) {} // define
#endif

#define __test_multiset 0
#if __test_multiset
#include <set>
#endif

#define __test_multimap 0
#if __test_multimap
#include <map>
#endif

#define __test_rvalue_to_lvalue 0
#if __test_rvalue_to_lvalue
template <typename T>
void foo(T &a)
{
    return;
}
template <typename T>
void FOO(T &&a)
{
    foo(a); //调用foo(T& a), 在其内部，a已经是左值引用
    // foo(std::forward<T>(a));//编译失败
    return;
}
#endif

#define __test_constCast 0
#if __test_constCast
void foo(int& i){
    i = 1919810;
}
#endif

struct Foo
{
    std::string s;
    std::shared_ptr<uint64_t> sp;

    int serialize(serial_Archiver& a){
    // int anotherFuncName(serial_Archiver& a){//缺少合适的serialize()，应当引发编译报错
        return a(sp,s);
    }
    
};

int main(int, char **)
{
    Buffer b;
    double d;
    uint32_t i;
    std::string s;
    std::vector<std::string> vec;
    std::stack<double> stk;
    std::queue<int64_t> que;
    std::priority_queue<uint32_t> pq;
    std::set<char> st;
    std::multiset<unsigned char> ms;
    std::unordered_set<std::string> us;
    std::unordered_multiset<std::string> ums;
    std::pair<int, std::string> pair;
    std::map<int, std::vector<double>> mp;
    std::multimap<int, std::vector<double>> mmp;
    std::unordered_map<int, std::vector<double>> ump;
    std::unordered_multimap<int, std::vector<double>> ummp;
    std::unique_ptr<std::unordered_set<double>> up;
    std::shared_ptr<std::unordered_set<uint64_t>> sp;
    Foo f;

    if (true)
    {
        // 空字符串
        {
            b.pop(b.getLength());
            s = "";
            serial_Archiver ao(b, serial_ArchiverType::out_binary_bigEndian);
            ao(s);
            s = "abc";
            serial_Archiver ai(b, serial_ArchiverType::in_binary_bigEndian);
            ai(s);
        }

        // 测试const&、右值引用
        {
            b.pop(b.getLength());
            i = 114514;
            auto const& ii = i;
            serial_Archiver ao(b, serial_ArchiverType::out_binary_littleEndian);
            ao(ii);
            serial_Archiver ai(b, serial_ArchiverType::in_binary_littleEndian);
            // ai(1919810);//尝试反序列化到右值身上。结果没问题，Archiver::operator()()把右值变成左值然后才传给底层
            auto&& iii = 1919810;
            ai(std::forward<int>(iii));//尝试反序列化到右值身上。结果没问题，Archiver::operator()()把右值变成左值然后才传给底层。这句结束后监视iii的值，能看到它变了
            i = 0;
        }

        {
            b.pop(b.getLength());
            serial_Archiver ar(b, serial_ArchiverType::out_binary_littleEndian);
            ar(std::string("abc\0d", 5));
            s.clear();
            serial_Archiver ab(b, serial_ArchiverType::in_binary_littleEndian);
            ab(s);
        }

        {
            b.pop(b.getLength());
            serial_Archiver ac(b, serial_ArchiverType::out_binary_bigEndian);
            ac(114.514);
            d = 0.0;
            serial_Archiver ad(b, serial_ArchiverType::in_binary_bigEndian);
            ad(d);
        }

        {
            b.pop(b.getLength());
            serial_Archiver ae(b, serial_ArchiverType::out_binary_littleEndian);
            ae(std::string("a\0b", 3), 114.514, (uint32_t)114514);
            s.clear();
            d = 0.0;
            i = 0;
            serial_Archiver af(b, serial_ArchiverType::in_binary_littleEndian);
            af(s, d);
            af(i);
        }

        {
            b.pop(b.getLength());
            vec = {"ab", std::string("c\0d", 3)};
            serial_Archiver ag(b, serial_ArchiverType::out_binary_littleEndian);
            ag(vec);
            vec.clear();
            serial_Archiver ah(b, serial_ArchiverType::in_binary_littleEndian);
            ah(vec);
        }

        // stack
        {
            b.pop(b.getLength());
            stk.push(1.2);
            stk.push(3.4);
            serial_Archiver ao(b, serial_ArchiverType::out_binary_bigEndian);
            ao(stk);
            while (!stk.empty())
                stk.pop();
            serial_Archiver ai(b, serial_ArchiverType::in_binary_bigEndian);
            ai(stk);
        }
        
        // multimap
        {
            b.pop(b.getLength());
            mmp.insert({
                {114514, std::vector<double>({114.514})},
                {114514, std::vector<double>({-114.514})},
                {1919810, std::vector<double>({1919.810})}
            });
            serial_Archiver ao(b, serial_ArchiverType::out_binary_littleEndian);
            ao(mmp);
            mmp.clear();
            serial_Archiver ai(b, serial_ArchiverType::in_binary_littleEndian);
            ai(mmp);
        }

        // unordered_map
        {
            b.pop(b.getLength());
            ump.insert({
                {114514, std::vector<double>({114.514})},
                {1919810, std::vector<double>({1919.810})}});
            serial_Archiver ao(b, serial_ArchiverType::out_binary_bigEndian);
            ao(ump);
            ump.clear();
            serial_Archiver ai(b, serial_ArchiverType::in_binary_bigEndian);
            ai(ump);
        }

        // unordered_multimap
        {
            b.pop(b.getLength());
            ummp.insert({{114514, std::vector<double>({114.514})},
                        {1919810, std::vector<double>({1919.810})}});
            serial_Archiver ao(b, serial_ArchiverType::out_binary_bigEndian);
            ao(ummp);
            ummp.clear();
            serial_Archiver ai(b, serial_ArchiverType::in_binary_bigEndian);
            ai(ummp);
        }

        // unique_ptr
        {
            b.pop(b.getLength());
            up = std::make_unique<std::unordered_set<double>>();
            up->insert({114.514, 1919.810});
            serial_Archiver ao(b, serial_ArchiverType::out_binary_littleEndian);
            ao(up);
            up = nullptr;
            serial_Archiver ai(b, serial_ArchiverType::in_binary_littleEndian);
            ai(up);
            for(auto& e : (*up)){
                std::cout << e << '\t';
            }   std::cout << std::endl;
        }
       
        // shared_ptr
        {
            b.pop(b.getLength());
            sp = std::make_shared<std::unordered_set<uint64_t>>();
            sp->insert({114514, 1919810});
            serial_Archiver ao(b, serial_ArchiverType::out_binary_bigEndian);
            ao(sp);
            sp = nullptr;
            serial_Archiver ai(b, serial_ArchiverType::in_binary_bigEndian);
            ai(sp);
        }

        // Foo
        {
            b.pop(b.getLength());
            serial_Archiver ao(b, serial_ArchiverType::out_binary_littleEndian);
            ao(Foo{
                std::string("a\0b",3),
                std::make_shared<uint64_t>(114514)
            });
            f = {};
            serial_Archiver ai(b, serial_ArchiverType::in_binary_littleEndian);
            ai(f);
        }

    }

    // Buffer b;
    // BinarySerializer bs(b, true);
    // bs(0x0102, std::string("abc"));

    // char data[8] = "abcdefg";
    // adaptEndian(data, 8, isBigEndian(), true);

    // char a,b;
    // a = 3; b = 4;
    // a = a^b; b = a^b; a = a^b;

    std::cout << "Hello, serial!\n";

#if __test_constCast
    const int iii = (114514);
    // iii = 1919810; expression must be a modifiable lvalue
    foo(const_cast<int&>(iii));//这里foo()成功改变了iii的值……GCC编译后这里iii会变，不能说明其它编译器也是这样。const_cast本身就是个未定义行为，去掉了const仅能说明iii不再被保证是常量，实际会不会变，难说
#endif

#if __test_rvalue_to_lvalue
    FOO(114514);
#endif

#if __test_multimap
    std::multimap<int, char> mm;
    mm.insert({{1, '1'}, {3, '3'}, {5, '5'}, {3, 3}});
    for (auto &kv : mm)
    {
        auto k = kv.first;
        auto v = kv.second;
    }
#endif

#if __test_multiset
    std::multiset<int> ms;
    ms.insert({1, 1, 2, 3, 3});
    std::cout << ms.size() << std::endl;
    for (auto &e : ms)
    {
        std::cout << e << '\t';
    }
    std::cout << std::endl;
#endif

#if __test_templateSplit
    std::vector<int> v;
    foo(v);
#endif

#if __test_templateExistence
    std::vector<int> v;
    // foo(v);不需要在这里“手动”展开
    auto res = FunctionExists_withParam_foo<std::vector<int> &>::result; // FunctionExists_withParam_foo::check()的decltype()部分“调用”了foo(), 所以foo模板被展开了，result为true；而且无论vector的模板参数填什么，只要别把vector的那版foo()删了，结果就都是true
#endif
}
