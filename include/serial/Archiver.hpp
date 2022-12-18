#if !defined(_Archiver_hpp)
#define _Archiver_hpp

#include <string.h>
#include <utility>
#include "./Buffer.hpp"
#include "./EnableIf.hpp"

#include "./MemberExistenceChecker.hpp"
CheckMemberFunctionExistence(serialize)
#include "./FunctionExistenceChecker.hpp"
CheckFunctionExistence_withParam(serialize)

#define ERR_NO_SERIALIZE_FUNC -2
#define ERR_BUFFER_FILLED -3
#define ERR_BUFFER_LACK_DATA -4
#define ERR_DATA_OBSCURE -5
#define ERR_UNKNOWN -114514

enum SerialType{
    out_binary_littleEndian
  , out_binary_bigEndian
  , in_binary_littleEndian
  , in_binary_bigEndian
};

class Archiver
{
public:

  Buffer& data;
  SerialType const type;

  Archiver(Buffer& b, SerialType t) : data(b), type(t) {}

  // memberOrNonMember()
  // 只要 serialize(Archiver&, T&) 存在，具体的序列化或反序列化就调用它；
  // 如果仅 T::serialize(Archiver&) 存在，具体的序列化或反序列化就调用 T对象.serialize()；
  // 如果两者都不存在，那么直接返回错误码。
  // 这几种情况的条件分支在编译期利用enable_if_t完成选择。

  /// @brief 调用非成员serialize()
  /// @tparam T 被序列化或反序列化的对象的类型
  /// @param a 被序列化或反序列化的对象
  /// @return 失败时，返回负数
  template <typename T,
            EnableIf_ptr<FunctionExists_withParam_serialize<Archiver&, T&>::result
                        > p = nullptr>
  int memberOrNonMember(T&& a){
    return serialize(*this, a);
  }

  /// @brief 调用成员函数T::serialize()
  /// @tparam T 被序列化或反序列化的对象的类型
  /// @param a 被序列化或反序列化的对象
  /// @return 失败时，返回负数
  template <typename T,
            EnableIf_ptr<!FunctionExists_withParam_serialize<Archiver&, T&>::result &&
                         HasMemberFunction_serialize<T>::result
                        > p = nullptr>
  int memberOrNonMember(T&& a){
    return a.serialize(*this);
  }

  /// @brief 没有合适的函数可以调用
  /// @tparam T 被序列化或反序列化的对象的类型
  /// @param a 被序列化或反序列化的对象
  /// @return ERR_NO_SERIALIZE_FUNC
  template <typename T, 
            EnableIf_ptr<!FunctionExists_withParam_serialize<Archiver&, T&>::result &&
                         !HasMemberFunction_serialize<T>::result
                        > p = nullptr>
  int memberOrNonMember(T&& a){return ERR_NO_SERIALIZE_FUNC;}

  // memberOrNonMember() //
  
  template <typename T> int prologue(T&& a){return 0;}

  template <typename T> int epilogue(T&& a){return 0;}

  template <typename T> int operator()(T&& a){
    // auto ret = prologue(std::forward<T>(a));
    // if(0>ret) return ret;
    // ret = memberOrNonMember(std::forward<T>(a));
    // if(0>ret) return ret;
    // return epilogue(std::forward<T>(a));
    // 好像没必要转发，左值也OK？试试看
    auto ret = prologue(a);
    if(0>ret) return ret;
    ret = memberOrNonMember(a);
    if(0>ret) return ret;
    return epilogue(a);
  }

  template <typename T0, typename ... Ts> int operator()(T0&& a0, Ts&& ... a){
    // auto ret = this->operator()(std::forward<T0>(a0));
    // if(0>ret) return ret;
    // return this->operator()(std::forward<Ts>(a)...);
    // 好像没必要转发，左值也OK？试试看
    auto ret = this->operator()(a0);
    if(0>ret) return ret;
    return this->operator()(a...);
  }
  
  ~Archiver(){}
};

#endif // _Archiver_hpp
