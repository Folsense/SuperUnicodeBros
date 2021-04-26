#ifndef NESEMU_NESROM_H
#define NESEMU_NESROM_H
#include "helper.h"

class Nesrom {
public:
    std::ifstream romFile;
    char magic[5];
    byte prgromlen;
    byte chrromlen;
    byte flags6;
    byte flags7;
    byte flags8;
    byte flags9;
    byte flags10;
    byte mirroring;
    char padding[6];
    char prgromchar[100 * 16384 + 1];
    char chrromchar[100 * 8192 + 1];
    byte prgrom[100 * 16384 + 1];
    byte chrrom[100 * 8192 + 1];
    Nesrom();
    void read();
};


#endif //NESEMU_NESROM_H
