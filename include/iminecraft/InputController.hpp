#ifndef _IMINECRAFT_INPUTCONTROLLER_HPP_
#define _IMINECRAFT_INPUTCONTROLLER_HPP_

#include <SDL/SDL.h>
#include <cstdlib>
#include <iostream>
#include "iminecraft/ControlCenter.hpp"
#include "iminecraft/Rendering.hpp"


using namespace std;

namespace iminecraft {
        class InputController{
            private:
                Uint32 timeStartForAverageFPS;
                int numFrames;

                bool leftClick;
                ControlCenter& controlCenter;

            public:
                InputController(ControlCenter& c_controlCenter);
                virtual ~InputController();

                bool processIntro();
                bool processEvent();
        };
}

#endif
