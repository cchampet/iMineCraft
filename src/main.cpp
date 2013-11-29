#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <omp.h>

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_ttf.h>
#include "SDL/SDL_mixer.h"
#include <GL/glew.h>

#include <sys/types.h>
#include <dirent.h>

#include <cstring>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imac2gl3/shader_tools.hpp"
#include "imac2gl3/shapes/common.hpp"
#include "imac2gl3/shapes/GLShapeInstance.hpp"

#include "imac2gl3/MatrixStack.hpp"
#include "imac2gl3/TextureTool.hpp"

#include "iminecraft/cameras/FirstPersonCamera.hpp"

#include "iminecraft/land/Chunk.hpp"
#include "iminecraft/land/BlockData.hpp"

#include "iminecraft/World.hpp"

#include "iminecraft/Rendering.hpp"
#include "iminecraft/InputController.hpp"

#include "iminecraft/ControlCenter.hpp"
#include "iminecraft/characters/CharactersGestion.hpp"

#include "iminecraft/sound/Music.hpp"


size_t WINDOW_WIDTH, WINDOW_HEIGHT;
static const int FRAMES_PER_SECOND = 60;
static const int MIN_LOOP_TIME = 1000 / FRAMES_PER_SECOND;

int volume = 64;

using namespace glm;
using namespace iminecraft;
using namespace std;


int main(int argc, char** argv) {
    /********************************************************************
     * INITIALISATION DU PROGRAMME
     ********************************************************************/

    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

	if(TTF_Init() == -1)
	{
	    std::cerr<<"Erreur d'initialisation de TTF_Init : "<<TTF_GetError()<<std::endl;
	    return (EXIT_FAILURE);
	}

	 int tid;
	 bool done = false;
	 bool muted = false;

	#pragma omp parallel shared(done) private(tid) num_threads(2)
    {

	tid = omp_get_thread_num();

    if(tid != 0){

    	Music ambiance;
    	if(ambiance.number() > 0){
    		ambiance.play();

    		unsigned int time_changed = 0;
    		bool changeMusic = false;

    		while(!done){
    			Uint32 timeStart = SDL_GetTicks();
    			Uint8 *keystates = SDL_GetKeyState(NULL);
    			if(keystates[SDLK_m]){
    				if(!muted)
    					ambiance.mute();
    				else{
    					ambiance.volume(0);
    				}
    				muted = !muted;
    			}
    			if(keystates[SDLK_KP_PLUS] || keystates[265])
    				ambiance.volume(2);
    			if(keystates[SDLK_KP_MINUS] || keystates[259])
    				ambiance.volume(-2);
    			if(keystates[SDLK_EQUALS] && time_changed > 30){
    				changeMusic = true;
    				time_changed = 0;
    			}
    			++time_changed;

    			if(changeMusic || ambiance.channel() < 0){
    				ambiance.next();
    				changeMusic = false;
    			}

    			Uint32 timeEnd = SDL_GetTicks();
    			if((int)(timeEnd - timeStart) < MIN_LOOP_TIME)
    				SDL_Delay(MIN_LOOP_TIME - (timeEnd - timeStart));
    		}
    	}

    }else{

    // Récuère les infos matériel vidéo
    const SDL_VideoInfo* myScreen = SDL_GetVideoInfo();

    // Creation de la fenêtre et d'un contexte OpenGL
    if(myScreen->current_w > 1980){
    	WINDOW_WIDTH = (myScreen->current_h*0.9)*(16./9.);
    	WINDOW_HEIGHT = myScreen->current_h*0.9;
    	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, myScreen->vfmt->BitsPerPixel, SDL_RESIZABLE | SDL_OPENGL);
    }else{
    	WINDOW_WIDTH = myScreen->current_w;
    	WINDOW_HEIGHT = myScreen->current_h;
    	SDL_SetVideoMode(myScreen->current_w, myScreen->current_h, myScreen->vfmt->BitsPerPixel, SDL_OPENGL | SDL_FULLSCREEN);
    }

    // Initialisation de GLEW
    GLenum error;
    if(GLEW_OK != (error = glewInit())) {
        std::cerr << "Impossible d'initialiser GLEW: " << glewGetErrorString(error) << std::endl;
        exit(1);
    }
    //Mix_HookMusicFinished(musicFinished);

    //Blocage de la souris dans la fenêtre
    SDL_WM_GrabInput(SDL_GRAB_ON);
    SDL_ShowCursor(SDL_DISABLE);

    // Gestion de la graine de génération de terrain
    int seed = 0;
    string seedFilePath = string("files/seed"); 
    ifstream seedFileIN(seedFilePath);
    if(!seedFileIN){
        // file do not exist
        srand(time(NULL));
        seed = rand();

        ofstream seedFileOUT(seedFilePath);
        if(!seedFileOUT.good()){
            throw ofstream::failure("'Save Chunk: fail to create file'");
        }else{
            seedFileOUT << seed;
            seedFileOUT.close();
        }
    }else{
        seedFileIN >> seed;
        seedFileIN.close();
    }
    //


    /**
     * CAMERA camera - just for test
     */
    FreeFlyCamera camera;
    FirstPersonCamera fpCam;

    /**
     * Store and manage Main character and others guys from the game
     */
    CharactersGestion charactersGestion;

    /**
     * Create the WORLD
     */
    World world(seed, charactersGestion.getHero().position().x, charactersGestion.getHero().position().z);
    
    /**
     * Class to render and display stuff
     */
    Rendering rend((World&) world, (FirstPersonCamera&) fpCam, (CharactersGestion&) charactersGestion);

    /**
     * The control tower, the brain !
     */
    ControlCenter controlCenter((World&) world, (CharactersGestion&) charactersGestion, (FirstPersonCamera&) fpCam);

    /**
     * Check and control input given by user
     */
    InputController inputController((ControlCenter&) controlCenter);

    // test to store data
    // BlockData blockData;
    // blockData.displayAllData();

    bool endIntro = false;

    // Boucle principale
    while(!done) {
        Uint32 timeStart = SDL_GetTicks();
        // Nettoyage de la fenêtre
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(endIntro){
            // time to display !!
            rend.renderWithIntro(false);

            // check input
            done = inputController.processEvent();

            // check jumps and neutral char movement
            controlCenter.processOther();
        }else{
            rend.renderWithIntro(true);
            // check input
            done = inputController.processIntro();
            endIntro = controlCenter.processIntro();
        }

        Uint32 timeEnd = SDL_GetTicks();
        if((int)(timeEnd - timeStart) < MIN_LOOP_TIME)
            SDL_Delay(MIN_LOOP_TIME - (timeEnd - timeStart));
    }

    }


    }
    // Destruction des ressources OpenGL

    /** PLACEZ VOTRE CODE DE DESTRUCTION DES VBOS/VAOS/SHADERS/... ICI **/
    Mix_CloseAudio();
    SDL_Quit();


    return EXIT_SUCCESS;
}

