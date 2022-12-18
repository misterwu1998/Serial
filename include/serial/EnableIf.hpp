#if !defined(_EnableIf_hpp)
#define _EnableIf_hpp

#include <type_traits>

#define __example_EnableIf 0

template <bool Condition> using EnableIf_ptr = typename std::enable_if<Condition, void>::type *;

#if __example_EnableIf

template <typename T, EnableIf_ptr<std::is_class<T>::value> p = nullptr>
void impl(T&& a){
  "Case 1.";
}

template <typename T, EnableIf_ptr<!std::is_class<T>::value> p = nullptr>
void impl(T&& a){
  "Case 2.";
}

#endif 

#undef __example_EnableIf

#endif // _EnableIf_hpp
