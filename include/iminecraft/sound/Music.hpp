/*
 * Music.hpp
 *
 *  Created on: 10 janv. 2013
 *      Author: florent
 */

#ifndef __IMINECRAFT_MUSIC_HPP_
#define __IMINECRAFT_MUSIC_HPP_

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include "SDL/SDL_mixer.h"

namespace iminecraft {

	class Music {
		private :
			int m_Volume;
			unsigned int m_Number;
			int m_Current;
			std::vector<Mix_Music*> m_Music;

		public:
			//static int m_Channel;
			Music();

			int number();
			int channel();
			void channel(int c);

			int play();
			void next();
			void mute();

			void volume(int v);

			//static void musicDone(){ m_Channel = -1;};

			virtual ~Music();
	};

	//int Music::m_Channel = -1;

} /* namespace iminecraft */


void musicDone();


#endif /* __IMINECRAFT_MUSIC_HPP_ */
