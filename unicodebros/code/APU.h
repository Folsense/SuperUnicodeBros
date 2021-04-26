#ifndef APU_H
#define APU_H

//Can't get a usable audio library working, I'll maybe try again later because I've spent too long on this

/*#undef Status
#include <SFML/Audio.hpp>
#include <stdio.h>
#include "../portaudio/include/portaudio.h"
#include <alsa/asoundlib.h>*/
#include "helper.h"
#include "Memory.h"

class APU {
public:
    Memory* mem;
    #if 0
    class CustomStream : public sf::SoundStream
    {
    public:
        bool load(sf::Int16** lsamples)
        {
            //buffer = &lbuffer;
            samples = lsamples;
            //m_samples.assign(buffer->getSamples(), buffer->getSamples() + buffer->getSampleCount());
            //m_currentSample = 0;
            initialize(1, 44100);
        }
    private:
        std::vector<sf::Int16> m_samples;
        std::size_t m_currentSample;
        sf::SoundBuffer* buffer;
        sf::Int16** samples;
    
        virtual bool onGetData(Chunk& data)
        {
            const int samplesToStream = 1000;

            //m_samples.assign(buffer->getSamples(), buffer->getSamples() + buffer->getSampleCount());
            m_currentSample = 0;

            data.samples = *samples;//&m_samples[m_currentSample];
            data.sampleCount = 1000;//buffer->getSampleCount();
            //std::cout << data.samples << '\n';
            // have we reached the end of the sound?
            //if (m_currentSample + samplesToStream <= m_samples.size())
            //{
            data.sampleCount = samplesToStream;
            return true;
            //}
            /*else
            {
                // end of stream reached: stream the remaining samples and stop playback
                data.sampleCount = m_samples.size() - m_currentSample;
                m_currentSample = m_samples.size();
                return true;
            }*/
        }
        virtual void onSeek(sf::Time timeOffset)
        {
            //m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
            //m_currentSample = 0;
        }
        };
    struct pulsewavestruct {
        byte duty;
        byte lengthctrhalt;
        byte constvolume;
        byte volume;
        byte sweepenabled;
        byte sweepperiod;
        byte sweepnegate;
        byte sweepshift;
        word timer;
        byte lengthctrload;
        byte length;
        float frequency;
        float samplesperbit;
        int samplelength;
        byte pattern;
        byte pos;
        double changepos;
        byte sweepctr;
        bool muted = false;
        int usepos;
        int numUpdates = 0;
        word targetperiod;
        float targetfrequency;
        float smalladds[30];
        byte sequence[32] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        /*sf::Sound channel;
        sf::SoundBuffer buffer;
        CustomStream stream;*/
         /* Handle for the PCM device */ 
        snd_pcm_t *pcm_handle;          

        /* Playback stream */
        snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;

        /* This structure contains information about    */
        /* the hardware and can be used to specify the  */      
        /* configuration to be used for the PCM stream. */ 
        snd_pcm_hw_params_t *hwparams;
        int error = 0;
        char pcm_name[11] = "plughw:0,0";

        sf::Int16 samples2[10][1000];
        sf::Int16** samples;
        sf::Int16* sampleptr;
        pulsewavestruct() {
            /*snd_pcm_hw_params_alloca(&hwparams);
            error = snd_pcm_open(&pcm_handle, pcm_name, stream, 0);
            if (error < 0) {
                fprintf(stderr, "Error opening PCM device %s\n", pcm_name);
                std::cout << error << '\n';
                exit(1);
            }
            error = snd_pcm_hw_params_any(pcm_handle, hwparams);
            if(error < 0){
                fprintf(stderr, "Can not configure this PCM device.\n");
                std::cout << error << '\n';
                exit(0);
            }
            for(float i = 0; i < 6.14; i += 0.204){
                smalladds[static_cast<int>(i)] = sin(i) / 8.0;
                //std::cout << smalladds[static_cast<int>(i)];
            }
            //buffer.loadFromSamples(samples, 1000, 1, 44100);
            sampleptr = samples2[0];
            samples = &sampleptr;*/
        }
        void setchannel(word addr, byte offset, Memory* mem){
            //if(addr % 0x4 == 0){
            duty = (mem->data[0x4000 + offset] & 0b11000000) >> 6;
            lengthctrhalt = (mem->data[0x4000 + offset] & 0b00100000) != 0;
            constvolume = (mem->data[0x4000 + offset] & 0b00010000) > 0;
            volume = mem->data[0x4000 + offset] & 0x0F;
            //} else {
            sweepenabled = (mem->data[0x4001 + offset] & 0b10000000) > 0;
            muted = false;
            sweepperiod = (mem->data[0x4001 + offset] & 0b01110000) >> 4;
            sweepperiod += 1;
            sweepctr = sweepperiod;
            sweepnegate = (mem->data[0x4001 + offset] & 0b00001000) != 0;
            sweepshift = mem->data[0x4001 + offset] & 0b00000111;
            timer = mem->data[0x4002 + offset] + ((mem->data[0x4003 + offset] & 0b00000111) << 8);
            timer += 1;
            if(timer < 8){
                muted = true;
            }
            lengthctrload = (mem->data[0x4003 + offset] & 0b11111000) >> 3;
            //std::cout << int(lengthctrhalt) << '\n';
            length = lengthctrload;
            frequency = 1789773.0 / (2 * (timer + 1));
            samplesperbit = 44100.0 / (1 * frequency);
            byte patterns[4] = {0b00000010, 0b00000110, 0b00011110, 0b11111001};
            pattern = patterns[duty];
            pos = 1;
            changepos = 0;
            usepos = 0;
            targetperiod = timer;
            if(sweepenabled){
                word changeamount = timer >> sweepshift;
                if(sweepnegate){
                    targetperiod = timer - changeamount;
                } else {
                    targetperiod = timer + changeamount;
                }
                targetfrequency = 1789773.0 / (2 * (targetperiod + 1));
            }
            //}
        }
        void updatechannel(){
            numUpdates += 1;
            float lastval = 0;
            word cyclesSinceLast = 0;
            for(int i = 0; i < 1000; i ++){
                if(i > 0 && i % 367 == 0){
                    if(sweepenabled && !muted){
                        sweepctr -= 1;
                        if(sweepctr == 0){
                            frequency = targetfrequency;
                            samplesperbit = 44100.0 / (1 * frequency);
                            timer = targetperiod;
                            word changeamount = timer >> sweepshift;
                            if(sweepnegate){
                                targetperiod = timer - changeamount;
                            } else {
                                targetperiod = timer + changeamount;
                            }
                            targetfrequency = 1789773.0 / (2 * (targetperiod + 1));
                            sweepctr = sweepperiod;
                            pos = 1;
                            usepos = 0;
                            changepos = 0;
                        }
                        if(1 / frequency < 8 || targetperiod > 0x7FF){
                            //muted = true;
                        }
                    }
                    if(!lengthctrhalt){
                        length -= 1;
                    }
                    if(length == 0){
                        //muted = true;
                    }
                }
                if(muted){
                    samples2[numUpdates % 10][i] = 0;    
                } else {
                cyclesSinceLast += 1;
                float val = (pattern & pos) != 0;
                if(lastval != val && cyclesSinceLast < samplesperbit * 0.1){
                    float waythere = cyclesSinceLast / (samplesperbit * 0.1);
                    val = waythere * val + (1 - waythere) * lastval;
                    //std::cout << waythere << '\n';
                }
                val += smalladds[i % 30];
                samples2[numUpdates % 10][i] = val * 15000.0 * volume / 15.0;
                //std::cout << samples[usepos] << '\n';
                if(samplesperbit > 0){
                while(usepos > changepos){
                    pos <<= 1;
                    if(pos == 0){
                        pos = 1;
                    }
                    //std::cout << int(pos) << '\n';
                    cyclesSinceLast = 0;
                    changepos += samplesperbit;
                    lastval = val;
                }
                }
                }
                usepos += 1;
            }
            sampleptr = samples2[numUpdates % 10];
            //buffer.loadFromSamples(samples2, 1000, 1, 44100);
            /*pos = 1;
            int i = 0;
            samplelength = 0;
            usepos = 0;
            changepos = samplesperbit;
            while(!muted && samplesperbit < 500 && samplesperbit > 0){
                if(i > 0 && i % 367 == 0){
                    if(sweepenabled && !muted){
                        sweepctr -= 1;
                        if(sweepctr == 0){
                            frequency = targetfrequency;
                            samplesperbit = 44100.0 / (1 * frequency);
                            timer = targetperiod;
                            word changeamount = timer >> sweepshift;
                            if(sweepnegate){
                                targetperiod = timer - changeamount;
                            } else {
                                targetperiod = timer + changeamount;
                            }
                            targetfrequency = 1789773.0 / (2 * (targetperiod + 1));
                            sweepctr = sweepperiod;
                            pos = 1;
                            usepos = 0;
                            changepos = 0;
                        }
                        if(1 / frequency < 8 || targetperiod > 0x7FF){
                            //muted = true;
                        }
                    }
                    if(lengthctr){
                    length -= 1;
                    }
                    if(lengthctr && length == 0){
                        muted = true;
                    }
                }
                if(muted){
                    samples[i] = 0;    
                } else {
                samples[i] = ((pattern & pos) > 0) * 32767 * volume / 15.0;
                if(samplesperbit > 0){
                while(usepos > changepos && pos != 0){
                    pos <<= 1;
                    if(pos == 0){
                        pos = 1;
                        if(samplelength > 9000){
                            break;
                        }
                    }
                    changepos += samplesperbit;
                }
                }
                usepos += 1;
                }
                i += 1;
                samplelength += 1;
                //std::cout << int(samplesperbit) << '\n';
            }*/
        }
    };
    struct trianglewavestruct {
        byte lengthctrhalt;
        byte linearctr;
        word timer;
        byte lengthctrload;
        byte length;
        float frequency;
        float samplesperbit;
        bool muted = false;
        dword usepos;
        float changepos;
        dword pos;
        int numUpdates = 0;
        sf::Sound channel;
        sf::SoundBuffer buffer;
        CustomStream stream;
        sf::Int16 samples2[10][1000];
        sf::Int16** samples;
        sf::Int16* sampleptr;
        trianglewavestruct() {
            //buffer.loadFromSamples(samples, 1000, 1, 44100);
            sampleptr = samples2[0];
            samples = &sampleptr;
            stream.load(samples);
            //stream.play();
            //exit(0);
        }
        void setchannel(word addr, Memory* mem){
            //if(addr % 0x4 == 0){
            lengthctrhalt = (mem->data[0x4008] & 0b10000000);
            linearctr = mem->data[0x4008] & 0b01111111;
            timer = mem->data[0x400A] + ((mem->data[0x400B] & 0b00000111) << 8);
            if(timer < 8){
                //muted = true;
            }
            lengthctrload = (mem->data[0x400B] & 0b11111000) >> 3;
            length = lengthctrload;
            frequency = 1789773.0 / (2 * (timer + 1));
            samplesperbit = 44100.0 / (1 * frequency);
            changepos = 0;
            usepos = 0;
            pos = 0;
            //}
        }
        byte sequence[32] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        void updatechannel(){
            numUpdates += 1;
            for(int i = 0; i < 1000; i ++){
                if(i > 0 && i % 367 == 0){
                    if(!lengthctrhalt){
                    length -= 1;
                    }
                    if(length == 0){
                        muted = true;
                    }
                }
                if(0){
                    samples2[numUpdates % 10][i] = 0;    
                } else {
                samples2[numUpdates % 10][i] = (static_cast<float>(sequence[pos % 32]) / 15.0) * 15000;
                usepos += 1;
                if(samplesperbit > 0){
                while(usepos > changepos){
                    changepos += samplesperbit;
                    pos += 1;
                }
                }
                }
            }
            sampleptr = samples2[numUpdates % 10];
        }
    };
    int ctr = 0;
    pulsewavestruct c1data;
    pulsewavestruct c2data;
    trianglewavestruct tdata;
    #endif
    APU();
    void update();
    void halt(byte data);
    void setchannel1(word index);
    void setchannel2(word index);
    void settriangle(word index);
    void updatechannel1();
    void updatechannel2();
    void updatetriangle();
};

#endif