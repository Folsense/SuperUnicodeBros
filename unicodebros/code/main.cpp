#include "Emulator.h"

int main(int argc, char** argv) {
    Emulator emulator;
    emulator.start();
    emulator.step();
    return 0;
}