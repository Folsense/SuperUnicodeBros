#include "APU.h"

APU::APU(){
    /*for(int i = 0; i < 10000; i ++){
        samples[i] = i % 32767;
    }
    buffer.loadFromSamples(samples, 10000, 1, 44100);
    sound.setBuffer(buffer);
    sound.play();*/
}

void APU::setchannel1(word addr){
    //c1data.setchannel(addr, 0, mem);
    
}

void APU::setchannel2(word addr){
    //c2data.setchannel(addr, 4, mem);
}

void APU::settriangle(word addr){
    //tdata.setchannel(addr, mem);
}

void APU::updatetriangle(){
    /*//triangle.stop();
    tdata.updatechannel(trianglesamples);
    trianglebuffer.loadFromSamples(trianglesamples, 10000, 1, 44100);
    triangle.setBuffer(trianglebuffer);
    triangle.play();*/
}

void APU::update(){
    /*ctr += 735;
    setchannel1(0x4000);
    setchannel2(0x4004);
    settriangle(0x4008);
    c1data.updatechannel();
    c2data.updatechannel();
    tdata.updatechannel();*/
}

void APU::halt(byte data){
    /*if(!(data & 1)){
    c1data.length = 0;
    c1data.muted = true;
    }
    if(!(data & 2)){
    c2data.length = 0;
    c2data.muted = true;
    }
    if(!(data & 4)){
    tdata.length = 0;
    tdata.muted = true;
    }*/
}