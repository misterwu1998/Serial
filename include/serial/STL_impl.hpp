#if !defined(_STL_impl_hpp)
#define _STL_impl_hpp

#include "./STL_decl.hpp"
#include "./Archiver.hpp"
#include "./EndianAdapter.hpp"

SERIAL_STL_1ARG_DECL(std::vector){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    // 遍历全部元素，递归序列化
    for(auto& e : obj){
      auto ret = a(e);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;
    
    for(; n>0; n--){
      obj.emplace_back();//要求E类型提供无参构造方法
      auto ret = a(obj[obj.size()-1]);
      if(0>ret) return ret;
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::stack){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    // 逆序，保证序列化数据的顺序就是入栈顺序
    std::stack<E> temp;
    while(!obj.empty()){
      temp.push(obj.top());
      obj.pop();
    }

    while(! temp.empty()){
      auto ret = a(temp.top());
      if(0>ret) return ret;
      temp.pop();
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      obj.push(E());//要求E类型提供无参构造方法
      auto ret = a(obj.top());
      if(0>ret) return ret;
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::queue){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    while(! obj.empty()){
      auto ret = a(obj.front());
      if(0>ret) return ret;
      obj.pop();
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      obj.push(E());//要求E类型提供无参构造方法
      auto ret = a(obj.back());
      if(0>ret) return ret;
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::priority_queue){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    while(! obj.empty()){
      auto ret = a(obj.top());
      if(0>ret) return ret;
      obj.pop();
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      E e; //要求E类型提供无参构造方法
      auto ret = a(e);
      if(0>ret) return ret;
      obj.push(e);
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::set){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    for(auto& e : obj){
      auto ret = a(e);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      E e; //要求E类型提供无参构造方法
      auto ret = a(e);
      if(0>ret) return ret;
      obj.insert(e);
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::multiset){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    for(auto& e : obj){
      auto ret = a(e);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      E e; //要求E类型提供无参构造方法
      auto ret = a(e);
      if(0>ret) return ret;
      obj.insert(e);
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::unordered_set){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    for(auto& e : obj){
      auto ret = a(e);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      E e;//要求E类型提供无参构造方法
      auto ret = a(e);
      if(0>ret) return ret;
      obj.insert(e);
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::unordered_multiset){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    for(auto& e : obj){
      auto ret = a(e);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      E e; //要求E类型提供无参构造方法
      auto ret = a(e);
      if(0>ret) return ret;
      obj.insert(e);
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_2ARG_DECL(std::pair){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    return a(obj.first, obj.second);
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_2ARG_DECL(std::map){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    for(auto& kv : obj){
      auto ret = a(kv.first, kv.second);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      K k; V v; //要求K,V类型提供无参构造方法
      auto ret = a(k,v);
      if(0>ret) return ret;
      obj.insert({k,v});
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_2ARG_DECL(std::multimap){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    for(auto& kv : obj){
      auto ret = a(kv.first, kv.second);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      K k; V v; //要求K,V类型提供无参构造方法
      auto ret = a(k,v);
      if(0>ret) return ret;
      obj.insert({k,v});
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_2ARG_DECL(std::unordered_map){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    for(auto& kv : obj){
      auto ret = a(kv.first, kv.second);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      K k; V v; //要求K,V类型提供无参构造方法
      auto ret = a(k,v);
      if(0>ret) return ret;
      obj.insert({k,v});
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_2ARG_DECL(std::unordered_multimap){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    uint32_t n = obj.size();
    auto wp = a.tempBuffer[sizeof(n)];
    if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    memcpy(wp, &n, sizeof(n));
    adaptEndian((char*)wp, sizeof(n), isBigEndian(), false);
    a.tempBuffer.push(sizeof(n));

    for(auto& kv : obj){
      auto ret = a(kv.first, kv.second);
      if(0>ret) return ret;
    }
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    // 开头是小端模式的4字节无符号整数记录元素个数
    if(4 + a.lenHandled > a.userBuffer.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    auto rp = a.dataStart + a.lenHandled;
    uint32_t n;
    memcpy(&n, rp, sizeof(n));
    adaptEndian((char*)(&n), sizeof(n), false, isBigEndian());
    a.lenHandled += 4;

    for(; n>0; n--){
      K k; V v; //要求K,V类型提供无参构造方法
      auto ret = a(k,v);
      if(0>ret) return ret;
      obj.insert({k,v});
    }
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::unique_ptr){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    if(!obj) return SERIAL_ERR_POINTER_NULL;
    return a(*obj);
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    obj = std::make_unique<E>();//要求E类型提供无参构造方法
    return a(*obj);
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_STL_1ARG_DECL(std::shared_ptr){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
  case serial_ArchiverType::out_binary_bigEndian:{
    if(!obj) return SERIAL_ERR_POINTER_NULL;
    return a(*obj);
  }
  break;
  case serial_ArchiverType::in_binary_littleEndian:
  case serial_ArchiverType::in_binary_bigEndian:{
    obj = std::make_shared<E>();//要求E类型提供无参构造方法
    return a(*obj);
  }
  break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

#endif // _STL_impl_hpp
