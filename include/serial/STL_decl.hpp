#if !defined(_STL_decl_hpp)
#define _STL_decl_hpp

class serial_Archiver;

#define SERIAL_STL_1ARG_DECL(std_classTemplate)\
template <typename E> int serialize(serial_Archiver& a, std_classTemplate<E>& obj)

#define SERIAL_STL_2ARG_DECL(std_classTemplate)\
template <typename K, typename V> int serialize(serial_Archiver& a, std_classTemplate<K,V>& obj)

#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <memory>

SERIAL_STL_1ARG_DECL(std::vector);
SERIAL_STL_1ARG_DECL(std::stack);
SERIAL_STL_1ARG_DECL(std::queue);
SERIAL_STL_1ARG_DECL(std::priority_queue);
SERIAL_STL_1ARG_DECL(std::set);
SERIAL_STL_1ARG_DECL(std::multiset);
SERIAL_STL_1ARG_DECL(std::unordered_set);
SERIAL_STL_1ARG_DECL(std::unordered_multiset);
SERIAL_STL_2ARG_DECL(std::pair);
SERIAL_STL_2ARG_DECL(std::map);
SERIAL_STL_2ARG_DECL(std::multimap);
SERIAL_STL_2ARG_DECL(std::unordered_map);
SERIAL_STL_2ARG_DECL(std::unordered_multimap);
SERIAL_STL_1ARG_DECL(std::unique_ptr);
SERIAL_STL_1ARG_DECL(std::shared_ptr);

#endif // _STL_decl_hpp
