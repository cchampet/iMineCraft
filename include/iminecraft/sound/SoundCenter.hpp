/*
 * SoundCenter.hpp
 *
 *  Created on: 8 janv. 2013
 *      Author: florent
 */

#ifndef SOUNDCENTER_HPP_
#define SOUNDCENTER_HPP_

/*#include <iostream>
#include <SDL/SDL_audio.h>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
#include "Sound.hpp"

using namespace iminecraft;

#pragma once
extern std::vector<Sound> soundList;
extern std::vector<Sound> playedSound;
extern SDL_AudioSpec fmt;


void initSounds();

void mixaudio(void *unused, Uint8 *stream, int len);
void PlaySound(size_t i);*/

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <queue>
#include <cmath>
#include "Sound.hpp"

const int AMPLITUDE = 28000;
const int FREQUENCY = 44100;

using namespace iminecraft;

struct SoundObject
{
    double freq;
    int samplesLeft;
};

class SoundCenter
{
private :
	double v;
	bool playingList[5];

public:
    std::queue<SoundObject> beeps;
    std::vector<Sound> soundList;
    std::vector<Sound> playedSound;

    SoundCenter();
    ~SoundCenter();
    void beep(double freq, int duration);
    void generateSamples(Sint16 *stream, int length);
    void PlaySound(size_t i);
    void wait();
};

void audio_callback(void*, Uint8*, int);




#endif /* SOUNDCENTER_HPP_ */
