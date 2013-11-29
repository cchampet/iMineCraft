/*
 * Music.hpp
 *
 *  Created on: 10 janv. 2013
 *      Author: florent
 */

#ifndef SOUNDS_HPP_
#define SOUNDS_HPP_

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include "SDL/SDL_mixer.h"

namespace iminecraft {

class Sounds {
private :
	int m_Volume;
	unsigned int m_Number;
	std::vector<Mix_Chunk*> m_Sounds;
	int m_Channel;

public:
	Sounds();

	int number();
	int channel();
	void channel(int c);

	int play(int i);
	void next();
	void mute();

	void volume(int v);

	virtual ~Sounds();
};

} /* namespace iminecraft */



#endif /* MUSIC_HPP_ */
