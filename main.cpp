#include <iostream>
#include <string>
#include "serial/EndianAdapter.hpp"
#include "serial/Archiver.hpp"
#include "serial/basic.hpp"

#define __test_templateExistence 0
#if __test_templateExistence
#include <vector>
template <typename E> void foo(std::vector<E>& v){}
#include <unordered_set>
template <typename E> void foo(std::unordered_set<E>& s){}
CheckFunctionExistence_withParam(foo)
#endif

int main(int, char**) {

#if __test_templateExistence
    std::vector<int> v;
    // foo(v);不需要在这里“手动”展开
    auto res = FunctionExists_withParam_foo<std::vector<int>&>::result;//FunctionExists_withParam_foo::check()的decltype()部分“调用”了foo(), 所以foo模板被展开了，result为true；而且无论vector的模板参数填什么，只要别把vector的那版foo()删了，结果就都是true
#endif

    Buffer b;
    double d;
    uint32_t i;
    std::string s;

    b.pop(b.getLength());
    serial_Archiver aa(b, serial_ArchiverType::out_binary_littleEndian);
    aa(std::string("abc\0d",5));
    s.clear();
    serial_Archiver ab(b, serial_ArchiverType::in_binary_littleEndian);
    ab(s);

    b.pop(b.getLength());
    serial_Archiver ac(b, serial_ArchiverType::out_binary_bigEndian);
    ac(114.514);
    d = 0.0;
    serial_Archiver ad(b, serial_ArchiverType::in_binary_bigEndian);
    ad(d);

    b.pop(b.getLength());
    serial_Archiver ae(b, serial_ArchiverType::out_binary_littleEndian);
    ae(std::string("a\0b",3), 114.514, (uint32_t)114514);
    s.clear(); d = 0.0; i=0;
    serial_Archiver af(b, serial_ArchiverType::in_binary_littleEndian);
    af(s,d);
    af(i);

    // Buffer b;
    // BinarySerializer bs(b, true);
    // bs(0x0102, std::string("abc"));

    // char data[8] = "abcdefg";
    // adaptEndian(data, 8, isBigEndian(), true);

    // char a,b;
    // a = 3; b = 4;
    // a = a^b; b = a^b; a = a^b;

    std::cout << "Hello, world!\n";
}
