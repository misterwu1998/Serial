#include <iostream>
#include <string>
#include "serial/EndianAdapter.hpp"
#include "serial/Archiver.hpp"
#include "serial/basic.hpp"

int main(int, char**) {
    Buffer b;
    double d;
    uint32_t i;
    std::string s;

    b.pop(b.getLength());
    Archiver aa(b, SerialType::out_binary_littleEndian);
    aa(std::string("abc\0d",5));
    s.clear();
    Archiver ab(b, SerialType::in_binary_littleEndian);
    ab(s);

    b.pop(b.getLength());
    Archiver ac(b, SerialType::out_binary_bigEndian);
    ac(114.514);
    d = 0.0;
    Archiver ad(b, SerialType::in_binary_bigEndian);
    ad(d);

    b.pop(b.getLength());
    Archiver ae(b, SerialType::out_binary_littleEndian);
    ae(std::string("a\0b",3), 114.514, (uint32_t)114514);
    s.clear(); d = 0.0; i=0;
    Archiver af(b, SerialType::in_binary_littleEndian);
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
