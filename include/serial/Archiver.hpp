#if !defined(_Archiver_hpp)
#define _Archiver_hpp

#include <string.h>
#include <utility>
#include "./Buffer.hpp"
#include "./EnableIf.hpp"
#include "./MemberExistenceChecker.hpp"
#include "./FunctionExistenceChecker.hpp"

#define SERIAL_ERR_NO_SERIALIZE_FUNC -2
#define SERIAL_ERR_BUFFER_FILLED -3
#define SERIAL_ERR_BUFFER_LACK_DATA -4
#define SERIAL_ERR_DATA_OBSCURE -5
#define SERIAL_ERR_POINTER_NULL -6
#define SERIAL_ERR_UNKNOWN -114514

CheckMemberFunctionExistence(serialize)
CheckFunctionExistence_withParam(serialize)

enum serial_ArchiverType{
    out_binary_littleEndian
  , out_binary_bigEndian
  , in_binary_littleEndian
  , in_binary_bigEndian
};

class serial_Archiver
{
private:

  serial_Archiver(serial_Archiver const& a)=delete;
  serial_Archiver(serial_Archiver&& a)=delete;
  serial_Archiver& operator=(serial_Archiver const& a){return *this;}

  /// @brief 如果调用栈上某层operator()是用户直接调用的，那么它很可能需要做特殊准备
  /// @return 
  int _prepare(){
    if(recursiveDepth==1){
      switch (this->type)
      {
      case serial_ArchiverType::out_binary_bigEndian:
      case serial_ArchiverType::out_binary_littleEndian:{

      }
        break;
      case serial_ArchiverType::in_binary_bigEndian:
      case serial_ArchiverType::in_binary_littleEndian:{
        // 那两条读指针的赋值
        if(data.getLength()==0) return SERIAL_ERR_BUFFER_LACK_DATA;
        dataStart = *data;
        lenHandled = 0;
      }
        break;
      default:
        return SERIAL_ERR_UNKNOWN;
      }
    }

    return 0;
  }

  /// @brief 如果调用栈上某层operator()是用户直接调用的，那么它很可能需要做特殊收尾
  /// @return 
  int _conclude(){
    if(recursiveDepth==1){
      switch (type)
      {
      case serial_ArchiverType::out_binary_littleEndian:
      case serial_ArchiverType::out_binary_bigEndian:
        break;
      case serial_ArchiverType::in_binary_littleEndian:
      case serial_ArchiverType::in_binary_bigEndian:{
        // 能够来到这里其实已经说明用户整个对象的反序列化成功了
        data.pop(lenHandled);//仅在这时弹出数据
        dataStart = NULL;
        lenHandled = 0;
      }
        break;
      default:
        return SERIAL_ERR_UNKNOWN;
      }
    }

    return 0;
  }

public:

  Buffer& data;
  serial_ArchiverType const type;

  serial_Archiver(Buffer& b, serial_ArchiverType t) : data(b), type(t), recursiveDepth(0), dataStart(NULL), lenHandled(0) {}

  /// @brief 在调用栈处于operator()时，记录当前是第几层递归，即，调用栈上当前有几个operator()
  unsigned int recursiveDepth;
  
  /// @brief 正在反序列化时，这个指针记录用户提供的整批数据的开头
  const void* dataStart;

  /// @brief 正在反序列化时，这个变量记录已经反序列化的数据长度（它们未从Buffer中被弹出，必须回到首层operator()确定了反序列化成功，才一次性弹出）
  unsigned int lenHandled;

  // memberOrNonMember()
  // 只要 serialize(serial_Archiver&, T&) 存在，具体的序列化或反序列化就调用它；
  // 如果仅 T::serialize(serial_Archiver&) 存在，具体的序列化或反序列化就调用 T对象.serialize()；
  // 如果两者都不存在，那么直接返回错误码。
  // 这几种情况的条件分支在编译期利用enable_if_t完成选择。

  // 另外，参数有没有被const修饰，完全是两个不同的重载，必须分开给出模板，
  // 否则const可能被夹在模板参数T中，导致编译期判定FunctionExists_withParam_serialize<serial_Archiver&, T&>::result、
  // HasMemberFunction_serialize<T>::result都为false。

  // 匹配没有被const修饰的对象

  /// @brief 调用非成员serialize()
  /// @tparam T 被序列化或反序列化的对象的类型
  /// @param a 被序列化或反序列化的对象
  /// @return 失败时，返回负数
  template <typename T,
            EnableIf_ptr<FunctionExists_withParam_serialize<serial_Archiver&, T&>::result
                        > p = nullptr>
  int memberOrNonMember(T& a){
    return serialize(*this, a);
  }

  /// @brief 调用成员函数T::serialize()
  /// @tparam T 被序列化或反序列化的对象的类型
  /// @param a 被序列化或反序列化的对象
  /// @return 失败时，返回负数
  template <typename T,
            EnableIf_ptr<!FunctionExists_withParam_serialize<serial_Archiver&, T&>::result &&
                         HasMemberFunction_serialize<T>::result
                        > p = nullptr>
  int memberOrNonMember(T& a){
    return a.serialize(*this);
  }

  /// @brief 没有合适的函数可以调用
  /// @tparam T 被序列化或反序列化的对象的类型
  /// @param a 被序列化或反序列化的对象
  /// @return SERIAL_ERR_NO_SERIALIZE_FUNC
  template <typename T, 
            EnableIf_ptr<!FunctionExists_withParam_serialize<serial_Archiver&, T&>::result &&
                         !HasMemberFunction_serialize<T>::result
                        > p = nullptr>
  int memberOrNonMember(T& a){
    return SERIAL_ERR_NO_SERIALIZE_FUNC;
  }

  // 匹配没有被const修饰的对象 //

  // 匹配被const修饰的对象

  /// @brief 调用非成员serialize()
  /// @tparam T 被序列化或反序列化的对象的类型
  /// @param a 被序列化或反序列化的对象（const&，但会通过const_cast被抹除）
  /// @return 失败时，返回负数
  template <typename T,
            EnableIf_ptr<FunctionExists_withParam_serialize<serial_Archiver&, T&>::result
                        > p = nullptr>
  int memberOrNonMember(T const& a){
    return serialize(*this, const_cast<T&>(a));
  }

  template <typename T,
            EnableIf_ptr<!FunctionExists_withParam_serialize<serial_Archiver&, T&>::result &&
                         HasMemberFunction_serialize<T>::result
                        > p = nullptr>
  int memberOrNonMember(T const& a){
    return a.serialize(*this);
  }

  /// @brief 没有合适的函数可以调用
  /// @tparam T 被序列化或反序列化的对象的类型
  /// @param a 被序列化或反序列化的对象（const&）
  /// @return SERIAL_ERR_NO_SERIALIZE_FUNC
  template <typename T, 
            EnableIf_ptr<!FunctionExists_withParam_serialize<serial_Archiver&, T&>::result &&
                         !HasMemberFunction_serialize<T>::result
                        > p = nullptr>
  int memberOrNonMember(T const& a){
    return SERIAL_ERR_NO_SERIALIZE_FUNC;
  }

  // 匹配被const修饰的对象 //

  // memberOrNonMember() //
  
  template <typename T> int prologue(T&& a){return 0;}

  template <typename T> int epilogue(T&& a){return 0;}

  template <typename T> int operator()(T&& a){
    recursiveDepth++;
    auto ret = _prepare();
    if(0>ret) return ret;

    ret = prologue(std::forward<T>(a));
    if(0>ret) return ret;
    ret = memberOrNonMember(a);//如果a是右值引用，传给memberOrNonMember()后将被变成左值引用
    if(0>ret) return ret;
    ret = epilogue(std::forward<T>(a));
    if(0>ret) return ret;

    ret = _conclude();
    if(0>ret) return ret;
    recursiveDepth--;
    return 0;
  }

  template <typename T0, typename ... Ts> int operator()(T0&& a0, Ts&& ... a){
    recursiveDepth++;
    auto ret = _prepare();
    if(0>ret) return ret;
    
    ret = this->operator()(std::forward<T0>(a0));
    if(0>ret) return ret;
    ret = this->operator()(std::forward<Ts>(a)...);
    if(0>ret) return ret;

    ret = _conclude();
    if(0>ret) return ret;
    recursiveDepth--;
    return 0;
  }
  
  ~serial_Archiver(){}
};

#endif // _Archiver_hpp
