/**
 * @file endian.hpp
 * @brief 
 * 
 * 一般操作系统都是小端，而通讯协议是大端的
 * 
 */

#if !defined(_endian_hpp)
#define _endian_hpp

/**
 * @brief 
 * 
 * @return true 本机属于大端模式
 * @return false 本机属于小端模式
 */
constexpr bool isBigEndian(){
  short a = 0x0100;
  return 0x01 == *((char*)&a);
}

/// @brief 
/// @param data 
/// @param dataLength 
/// @param bigEndianNow 目前数据符合大端模式
/// @param toBigEndian 处理后数据要符合大端模式吗？
static void adaptEndian(char* data, unsigned int dataLength, bool bigEndianNow, bool toBigEndian){
  if(bigEndianNow!=toBigEndian){
    for(unsigned int i=0; (i<<1)+1 < dataLength; i++){
      data[i] = data[i]^data[dataLength-1-i];
      data[dataLength-1-i] = data[i]^data[dataLength-1-i];
      data[i] = data[i]^data[dataLength-1-i];
    }
  }
}


#endif // _endian_hpp
