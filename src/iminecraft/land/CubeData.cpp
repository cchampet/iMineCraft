#include "iminecraft/land/CubeData.hpp"

namespace iminecraft {
    // Constructeur
    CubeData::CubeData(int _type/*, bool _visible*/){
        setType(_type);
        // visible = _visible;
        // if(visible){
       	// 	faceVisible_front 	= true;
        //     faceVisible_back 	= true;
        //     faceVisible_top 	= true;
        //     faceVisible_bottom 	= true;
        //     faceVisible_left 	= true;
        //     faceVisible_right 	= true;
        // }
    }

    void CubeData::setType(int _type){
        type = _type;
        switch(type){
            case 1 : // water
                durability = 1;
                break;

            case 2 : // sand
                durability = 2;
                break;

            case 3 : // rock
                durability = 7;
                break;

            case 4 : // earth
                durability = 4;
                break;

            case 5 : // lava
                durability = 1;
                break;

            case 6 : // wood
                durability = 3;
                break;

            case 7 : // leaf
                durability = 2;
                break;

            case 8 : // glowstone
                durability = 1;
                break;

            default : // void
                durability = 0;
                break;
        }
    }

    // destructeur
    CubeData::~CubeData(){

    }
}
