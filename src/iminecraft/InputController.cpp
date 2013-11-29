#include "iminecraft/InputController.hpp"

namespace iminecraft {
    // Constructeur
    InputController::InputController(ControlCenter& c_controlCenter) : controlCenter(c_controlCenter) {
        timeStartForAverageFPS = SDL_GetTicks();
        numFrames = 0;
        leftClick = false;
    }

    bool InputController::processIntro(){

        // Boucle de gestion des évenements
        SDL_Event e;
        Uint8 *keystates = SDL_GetKeyState(NULL);
        if(keystates[SDLK_ESCAPE])
            return true;
        if(keystates[SDLK_m])
            controlCenter.muteSound();

        if(keystates[SDLK_LALT] && keystates[SDLK_TAB]){
            SDL_WM_GrabInput(SDL_GRAB_OFF);
            SDL_ShowCursor(SDL_ENABLE);
        }
        /*if(keystates[SDLK_RSHIFT] && keystates[13]) //shift + enter
        	SDL_SetVideoMode(600, 600, GL_FALSE, SDL_RESIZABLE | SDL_OPENGL);*/




        while(SDL_PollEvent(&e)) {
            // Traitement de l'évenement fermeture de fenêtre
            if(e.type == SDL_QUIT)
                return true;

            switch (e.type){
                case SDL_MOUSEMOTION:
                    controlCenter.rotate(e.motion.xrel, e.motion.yrel);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_WM_GrabInput(SDL_GRAB_ON);
                    SDL_ShowCursor(SDL_DISABLE);
                    break;

                case SDL_KEYDOWN:
                	if((!keystates[SDLK_LALT] || !keystates[SDLK_TAB]) && !keystates[SDLK_KP_PLUS] && !keystates[SDLK_KP_MINUS] && !keystates[SDLK_m] && !keystates[SDLK_EQUALS]){
                		controlCenter.startProcessIntro();
                	}
                	break;
            }
        }

        return false;
    }

    bool InputController::processEvent(){
    	//size_t beginnigTime = SDL_GetTicks();
    	++numFrames;

        // Boucle de gestion des évenements
        SDL_Event e;
        Uint8 *keystates = SDL_GetKeyState(NULL);

        bool bMouseWheel = false;

        if(keystates[SDLK_ESCAPE]){
        	controlCenter.saveGame();
            return true;
        }


        // FPS
        if(numFrames > 300){
            // reset toutes les 10 secondes
            timeStartForAverageFPS = SDL_GetTicks();
            numFrames = 0;
        }
        if(keystates[SDLK_f]){
            float fps = ( numFrames/(float)(SDL_GetTicks() - timeStartForAverageFPS) )*1000;
            std::cout << fps << std::endl;
        }

        if(keystates[SDLK_n])
            controlCenter.changeNight();

        if(keystates[SDLK_z] || keystates[SDLK_UP])
            controlCenter.moveFrontHero();
        if(keystates[SDLK_s] || keystates[SDLK_DOWN])
            controlCenter.moveBackHero();
        if(keystates[SDLK_q] || keystates[SDLK_LEFT])
            controlCenter.moveLeftHero();
        if(keystates[SDLK_d] || keystates[SDLK_RIGHT])
            controlCenter.moveRightHero();
        if(keystates[SDLK_a])
            controlCenter.rotateLeft(-5.);
        if(keystates[SDLK_e])
            controlCenter.rotateLeft(5.);
        if(keystates[SDLK_r])
            controlCenter.saveGame();
        if(keystates[SDLK_m])
            controlCenter.muteSound();
        if(keystates[SDLK_KP_PLUS])
        	controlCenter.volumeSound(2);
        if(keystates[SDLK_KP_MINUS])
        	controlCenter.volumeSound(-2);
        if(keystates[SDLK_SPACE] || keystates[SDLK_RSHIFT] || keystates[SDLK_0] || keystates[SDLK_INSERT])
            controlCenter.jumpHero();
        if(keystates[SDLK_LALT] && keystates[SDLK_TAB]){
            SDL_WM_GrabInput(SDL_GRAB_OFF);
            SDL_ShowCursor(SDL_ENABLE);
        }
        /*if(keystates[SDLK_RSHIFT] && keystates[SDLK_KP_ENTER])
        	SDL_SetVideoMode(600, 600, GL_FALSE, SDL_RESIZABLE | SDL_OPENGL);*/

        // if(bCamera && keystate[SDLK_SPACE])
        //     fpCam.moveUp(.25f);

        // if(bCamera && keystate[SDLK_LCTRL])
        //     fpCam.moveUp(- .25f);


        while(SDL_PollEvent(&e)) {
            // Traitement de l'évenement fermeture de fenêtre
            if(e.type == SDL_QUIT){
            	controlCenter.saveGame();
            	return true;
            }


            // if(e.key.keysym.sym == SDLK_END){
            //     if(bCamera){
            //         camera = new iminecraft::FreeFlyCamera();
            //         bCamera = !bCamera;
            //     }else{
            //         camera = fpCam;
            //         bCamera = !bCamera;
            //     }
            // }

            switch (e.type){

				case SDL_VIDEORESIZE :
					//resize the window
					SDL_SetVideoMode(e.resize.w, e.resize.h, GL_FALSE, SDL_RESIZABLE | SDL_OPENGL);
					break;

                case SDL_MOUSEMOTION:
                    controlCenter.rotate(e.motion.xrel, e.motion.yrel);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_WM_GrabInput(SDL_GRAB_ON);
                    SDL_ShowCursor(SDL_DISABLE);
                    if((int)e.button.button == 1){ // left
                    	leftClick = true;
                    }
                    if((int)e.button.button == 3){ // right
                    	controlCenter.rightClickLand();
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if((int)e.button.button == 1){ // right
                    	leftClick = false;
                    }
                    break;

                case SDL_KEYDOWN:
                	switch(e.key.keysym.sym){

                		case 38:
							controlCenter.changeMaterial(0);
							break;

                		case 233:
							controlCenter.changeMaterial(1);
							break;

                		case 34:
							controlCenter.changeMaterial(2);
							break;

                		case 39:
							controlCenter.changeMaterial(3);
							break;

                		case 40:
							controlCenter.changeMaterial(4);
							break;

                		case 45:
							controlCenter.changeMaterial(5);
							break;

                		case 232:
							controlCenter.changeMaterial(6);
							break;

                		case 95:
							controlCenter.changeMaterial(7);
							break;

                		case 231:
							controlCenter.changeMaterial(8);
							break;

                		case 224:
							controlCenter.changeMaterial(9);
							break;

                		default :
                			//std::cerr<<e.key.keysym.sym<<std::endl;
                			break;
                	}
                	break;

                default:
                    break;
            }

            /*if(e.button.button == SDL_BUTTON_WHEELUP && !bMouseWheel){
            	controlCenter.changeMaterialDown();
            	bMouseWheel = true;
            }else */if(e.button.button == SDL_BUTTON_WHEELDOWN && !bMouseWheel){
            	controlCenter.changeMaterialUp();
            	bMouseWheel = true;

            }

        }

    	if(leftClick){
    		controlCenter.leftClickLand();
    	}

        //std::cerr<<SDL_GetTicks()-beginnigTime<<" ms"<<std::endl;

        return false;
    }

    // destructeur
    InputController::~InputController(){

    }
}
