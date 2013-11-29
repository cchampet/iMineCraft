/*
 * Sound.hpp
 *
 *  Created on: 8 janv. 2013
 *      Author: florent
 */

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <SDL/SDL_audio.h>

namespace iminecraft {

class Sound {

private :
	char* filename;

public:
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;

	Sound(char* filename);
	Sound(const Sound &s);

	char* getFileName();
	Uint8* getData();

	virtual ~Sound();
};

} /* namespace imac2gl3 */
#endif /* SOUND_HPP_ */

