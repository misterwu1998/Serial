#include "serial/basic.hpp"
#include "serial/Archiver.hpp"
#include "serial/EndianAdapter.hpp"

#define __basic_out_endianAdapted(bool_toBigEndian)\
{\
  auto wp = a.data[sizeof(obj)]; if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;\
  memcpy(wp, &obj, sizeof(obj));\
  adaptEndian((char*)wp, sizeof(obj), isBigEndian(), bool_toBigEndian);\
  a.data.push(sizeof(obj));\
}

#define __basic_in_endianAdapted(bool_fromBigEndian)\
{\
  if(a.dataStart==NULL) return SERIAL_ERR_UNKNOWN;\
  if(a.lenHandled + sizeof(obj) > a.data.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;\
  memcpy(&obj, a.dataStart + a.lenHandled, sizeof(obj));\
  adaptEndian((char*)(&obj), sizeof(obj), bool_fromBigEndian, isBigEndian());\
  a.lenHandled += sizeof(obj);\
}

SERIAL_BASIC_DECL(char){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(unsigned char){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(int16_t){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(uint16_t){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(int32_t){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(uint32_t){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(int64_t){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(uint64_t){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(float){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(double){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    __basic_out_endianAdapted(false)
    break;
  case serial_ArchiverType::out_binary_bigEndian:
    __basic_out_endianAdapted(true)
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    __basic_in_endianAdapted(false)
    break;
  case serial_ArchiverType::in_binary_bigEndian:
    __basic_in_endianAdapted(true)
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}

SERIAL_BASIC_DECL(std::string){
  switch (a.type)
  {
  case serial_ArchiverType::out_binary_littleEndian:
    // 同大端模式
    // break;
  case serial_ArchiverType::out_binary_bigEndian:                                                          {
    if(obj.empty()) return 0;
    // 统计待转义字符的个数
    uint32_t nEscape = 0;
    for(auto c : obj){//不包括收尾的空字符
      if(c=='\\' || c=='\0'){
        nEscape++;
      }
    }

    char* wp = (char*)(a.data[obj.size() + nEscape + 1]); if(NULL==wp) return SERIAL_ERR_BUFFER_FILLED;
    for(auto c : obj){//不包括收尾的空字符
      if(c=='\\' || c=='\0'){
        *wp = '\\';
        wp += 1;
      }
      *wp = c;
      wp += 1;
    }
    *wp = '\0';//收尾的空字符

    a.data.push(obj.size() + nEscape + 1);                                                        }
    break;
  case serial_ArchiverType::in_binary_littleEndian:
    // 同大端模式
    // break;
  case serial_ArchiverType::in_binary_bigEndian:{
    if(a.dataStart==NULL) return SERIAL_ERR_UNKNOWN;
    if(a.lenHandled>=a.data.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;
    const char* rp = (const char*)(a.dataStart + a.lenHandled);

    // 统计原文长度
    uint32_t len=0;//原文长度
    uint32_t i=0; while(true){
      if(a.lenHandled + i >= a.data.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA;//缺收尾符
      
      if(rp[i]==0) break;//收尾符
      if(rp[i]=='\\'){//反斜杠
        if(i+1>=a.data.getLength()) return SERIAL_ERR_BUFFER_LACK_DATA; //反斜杠后面不能没数据了
        i++;//跳过反斜杠
        if(rp[i]!='\\' && rp[i]!='\0') return SERIAL_ERR_DATA_OBSCURE;//逃逸字符仅允许2种
        len++;//有效长度加1
        i++;//下一个
      }else{//普通字符
        len++;//有效长度加1
        i++;//下一个
      }
    }
    
    obj = std::string(len,'\0');
    i=0; for(auto& c : obj){
      if(rp[i]=='\\') i++;//这次碰到反斜杠就直接跳过
      c = rp[i];
      i++;
    }//此时，i等于buffer中被遍历的数据量，但[i]收尾符未被遍历

    a.lenHandled += (i+1);
  }
    break;
  default:
    return SERIAL_ERR_UNKNOWN;
  }
  return 0;
}
