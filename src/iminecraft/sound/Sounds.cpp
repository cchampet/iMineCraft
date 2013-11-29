/*
 * Sounds.cpp
 *
 *  Created on: 10 janv. 2013
 *      Author: florent
 */

#include "iminecraft/sound/Sounds.hpp"

namespace iminecraft {

Sounds::Sounds() {

	srand(time(0));
	
	m_Volume = 64;
	m_Number = 0;


	m_Sounds.push_back(Mix_LoadWAV("sound/attacked.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/attack.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/add.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/delete.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/pas.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/saut.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/vache.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/mouton.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/cochon.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/poule.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/monstre.wav"));
	m_Sounds.push_back(Mix_LoadWAV("sound/cri.wav"));
	m_Number = m_Sounds.size();

	Mix_Volume(-1, m_Volume);

}


int Sounds::number(){
	return m_Number;
}

int Sounds::channel(){
	return m_Channel;
}

void Sounds::channel(int c){
	m_Channel = c;
}


int Sounds::play(int i){
	if(i >= 0 && (size_t)i < m_Number){
		m_Channel = Mix_PlayChannel(-1, m_Sounds[(size_t)i], 0);
		//if( m_Channel == -1) { std::cerr<<"Unable to load Sounds file: "<< Mix_GetError()<<std::endl;}
		return m_Channel;
	}
	return -1;
}


void Sounds::mute(){
	for(size_t i = 0; i< m_Number; ++i)
		Mix_VolumeChunk(m_Sounds[i], 0);
}


void Sounds::volume(int v){
	m_Volume = (m_Volume + v < 0) ? 0 : ((m_Volume + v > 128) ? 128 : m_Volume + v);
	//std::cerr<<m_Volume<<std::endl;
	for(size_t i = 0; i< m_Number; ++i)
		Mix_VolumeChunk(m_Sounds[i], m_Volume);
	//Mix_Volume(-1, m_Volume);
}




Sounds::~Sounds() {
	// TODO Auto-generated destructor stub
    for(size_t i=0; i<m_Number; ++i){
    	if(m_Sounds[i]){
    		Mix_FreeChunk(m_Sounds[i]);
    	}
    }
}

} /* namespace iminecraft */
