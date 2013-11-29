/*
 * Music.cpp
 *
 *  Created on: 10 janv. 2013
 *      Author: florent
 */

#include "iminecraft/sound/Music.hpp"

static int m_Channel = -1;

namespace iminecraft {

	Music::Music(){

		srand(time(0));
		int audio_rate = 22050;
		Uint16 audio_format = AUDIO_S16SYS;
		int audio_channels = 2;
		int audio_buffers = 4096;
		m_Volume = 64;
		m_Number = 0;

		// TODO Auto-generated constructor stub
		struct dirent *lecture;
		DIR *rep;
		std::string musicDir = "music";
		rep = opendir(musicDir.c_str());
		while ((lecture = readdir(rep))) {
			std::string musicName = lecture->d_name;
			if(musicName.find(".") != 0 && lecture->d_type != DT_DIR){
				++m_Number;
				//std::cerr<<lecture->d_name<<std::endl;
			}
		}

		closedir(rep);
		if(m_Number > 0){
			m_Music.resize(m_Number);

			if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
				std::cerr<<"Unable to initialize audio: "<<Mix_GetError()<<std::endl;
				exit(1);
			}

			size_t piste = 0;
			rep = opendir(musicDir.c_str());
			while ((lecture = readdir(rep))) {
				std::string musicName = lecture->d_name;
				if(musicName.find(".") != 0 && lecture->d_type != DT_DIR){
					std::string fullName = musicDir;
					fullName.append("/").append(musicName);
					m_Music[piste] = Mix_LoadMUS(fullName.c_str());
					if(!m_Music[piste]) std::cerr<<"Erreur lors du chargement de la musique : "<<fullName.c_str()<<std::endl;
					++piste;
				}
			}
			closedir(rep);

			m_Current = rand()%m_Number;
		}

	}


	int Music::number(){
		return m_Number;
	}

	int Music::channel(){
		return m_Channel;
	}

	void Music::channel(int c){
		m_Channel = c;
	}


	int Music::play(){
		Mix_HaltMusic();
		int ch = Mix_PlayMusic(m_Music[m_Current], 0);
		if( ch == -1) { std::cerr<<"Unable to load music file: "<< Mix_GetError()<<std::endl;}
		channel(ch);
		Mix_HookMusicFinished(musicDone);
		return ch;
	}


	void Music::next(){
		int next = rand()%m_Number;
		if(next == m_Current && m_Number > 1)
			next = (m_Current+1)%m_Number;

		m_Current = next;
		play();
	}


	void Music::mute(){
		Mix_VolumeMusic(0);
	}



	void Music::volume(int v){
		m_Volume = (m_Volume + v < 0) ? 0 : ((m_Volume + v > 128) ? 128 : m_Volume + v);
		Mix_VolumeMusic(m_Volume);
	}




	Music::~Music() {
		// TODO Auto-generated destructor stub
	    Mix_HaltMusic();
	    for(unsigned int i=0; i<m_Number; ++i){
	    	if(m_Music[i]){
	    		Mix_FreeMusic(m_Music[i]);
	    	}
	    }
	    //Mix_CloseAudio();
	}

} /* namespace iminecraft */

void musicDone(){
	Mix_HaltMusic();
	//std::cerr<<"Music suivante"<<std::endl;
	//iminecraft::Music::musicDone();
	//iminecraft::Music::m_Channel  = -1;
	m_Channel = -1;
}
