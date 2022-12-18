#if !defined(_basic_hpp)
#define _basic_hpp

#include <inttypes.h>
#include <string>

class Archiver;

#define __basic_serialize_decl_gen(Type)\
int serialize(Archiver& a, Type & obj)

__basic_serialize_decl_gen(char);
__basic_serialize_decl_gen(unsigned char);
__basic_serialize_decl_gen(int16_t);
__basic_serialize_decl_gen(uint16_t);
__basic_serialize_decl_gen(int32_t);
__basic_serialize_decl_gen(uint32_t);
__basic_serialize_decl_gen(int64_t);
__basic_serialize_decl_gen(uint64_t);
__basic_serialize_decl_gen(float);
__basic_serialize_decl_gen(double);
__basic_serialize_decl_gen(std::string);

#endif // _basic_hpp
