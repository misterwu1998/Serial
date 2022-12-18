#if !defined(_basic_hpp)
#define _basic_hpp

#include <inttypes.h>
#include <string>

class serial_Archiver;

#define SERIAL_BASIC_DECL(Type)\
int serialize(serial_Archiver& a, Type & obj)

SERIAL_BASIC_DECL(char);
SERIAL_BASIC_DECL(unsigned char);
SERIAL_BASIC_DECL(int16_t);
SERIAL_BASIC_DECL(uint16_t);
SERIAL_BASIC_DECL(int32_t);
SERIAL_BASIC_DECL(uint32_t);
SERIAL_BASIC_DECL(int64_t);
SERIAL_BASIC_DECL(uint64_t);
SERIAL_BASIC_DECL(float);
SERIAL_BASIC_DECL(double);
SERIAL_BASIC_DECL(std::string);

#endif // _basic_hpp
