#if !defined(_FunctionExistenceChecker_hpp)
#define _FunctionExistenceChecker_hpp

#include <type_traits>

#define __example_FunctionExistenceChecker 0

/// 使用当前宏，然后指定 FunctionExists_withParam_##functionName 结构体模板的模板参数为待检测函数的形参列表（按顺序）。
/// 目前找不到很好的办法来应对无参数的函数，以下模板指定模板参数为<void>并不能准确反映无参函数的存在性。
/// 写出模板参数为void的特化，在其中decltype部分“调用”无参函数也不可行，因为一旦对应的无参函数不存在，“调用”就立即引发编译器报错，称functionName是未定义的。
#define CheckFunctionExistence_withParam(functionName)\
\
template <typename T0, typename ... Ts>\
struct FunctionExists_withParam_##functionName{\
private:\
  template <typename A0, typename ... As>\
  static auto check(int _placeholder) -> decltype(functionName(std::declval<A0>(), std::declval<As>()...), std::true_type());\
  template <typename A0, typename ... As>\
  static std::false_type check(...);\
public:\
  static constexpr bool result = std::is_same<std::true_type, decltype(check<T0, Ts...>(114514))>::value;\
};

#if __example_FunctionExistenceChecker

#include <string>

// int foo(char c, int i, double d, std::string s){return 0;}
int foo(){return 0;}
int foo(int& i, std::string&& s){}

CheckFunctionExistence_withParam(foo)

void test_FunctionExistenceChecker(){
  bool res;
  res = FunctionExists_withParam_foo<void>::result;//并不能准确反映无参foo()的存在
  res = FunctionExists_withParam_foo<char>::result;
  res = FunctionExists_withParam_foo<std::string>::result;
  res = FunctionExists_withParam_foo<char,int,double,std::string>::result;
  res = FunctionExists_withParam_foo<char,int,double,std::string, const char*>::result;
  res = FunctionExists_withParam_foo<int&, std::string&&>::result;
  res = FunctionExists_withParam_foo<int&, std::string const&>::result;
}
#endif

#undef __example_FunctionExistenceChecker

#endif // _FunctionExistenceChecker_hpp
