#if !defined(_MemberExistenceChecker_hpp)
#define _MemberExistenceChecker_hpp

/// 使用当前宏，然后指定 HasMemberFunction_##memberFunction 的模板参数为待探测的类
#define CheckMemberFunctionExistence(memberFunction)\
template<typename Type_checked>\
struct HasMemberFunction_##memberFunction {\
private:\
  template<typename U>\
  static auto check(int _placeholder) -> decltype(&U::memberFunction, std::true_type());\
  template<typename U>\
  static std::false_type check(...);\
public:\
  static constexpr bool result = std::is_same<std::true_type, decltype(check<Type_checked>(114514))>::value;/* @brief 编译期检查结果 */\
};

/// 使用当前宏，然后指定 HasMemberVarOrConst_##memberVarOrConst 的模板参数为待探测的类
#define CheckMemberVarOrConstExistence(memberVarOrConst)\
template<typename Type_checked>\
struct HasMemberVarOrConst_##memberVarOrConst {\
private:\
  template<typename U>\
  static auto check(int _placeholder) -> decltype(&U::memberVarOrConst , std::true_type());\
  template<typename U>\
  static std::false_type check(...);\
public:\
  static constexpr bool result = std::is_same<std::true_type, decltype(check<Type_checked>(114514))>::value;/* @brief 编译期检查结果 */\
};

/// 使用当前宏，然后指定 HasStaticMemberFunc_##staticMemberFunc 的模板参数为待探测的类
#define CheckStaticMemberFuncExistence(staticMemberFunc)\
template<typename Type_checked>\
struct HasStaticMemberFunc_##staticMemberFunc {\
private:\
  template<typename U>\
  static auto check(int _placeholder) -> decltype(U::staticMemberFunc , std::true_type());\
  template<typename U>\
  static std::false_type check(...);\
public:\
  static constexpr bool result = std::is_same<std::true_type, decltype(check<Type_checked>(114514))>::value;/* @brief 编译期检查结果 */\
};

/// 使用当前宏，然后指定 HasStaticMemberVarOrConst_##staticMemberVarOrConst 的模板参数为待探测的类
#define CheckStaticMemberVarOrConstExistence(staticMemberVarOrConst)\
template<typename Type_checked>\
struct HasStaticMemberVarOrConst_##staticMemberVarOrConst {\
private:\
  template<typename U>\
  static auto check(int _placeholder) -> decltype(U:: staticMemberVarOrConst , std::true_type());\
  template<typename U>\
  static std::false_type check(...);\
public:\
  static constexpr bool result = std::is_same<std::true_type, decltype(check<Type_checked>(114514))>::value;/* @brief 编译期检查结果 */\
};

#endif // _MemberExistenceChecker_hpp
