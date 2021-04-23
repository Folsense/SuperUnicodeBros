#ifndef NESEMU_HELPER_CPP
#define NESEMU_HELPER_CPP

#include "helper.h"

sbyte byteToSbyte(byte in){
    sbyte out = 0xff;
    return static_cast<sbyte>(out) & static_cast<byte>(in);
}

#endif