#ifndef _IMINECRAFT_CUBEDATA_HPP_
#define _IMINECRAFT_CUBEDATA_HPP_

namespace iminecraft {
    class CubeData{
        private:
            int type;
            int durability;
            // bool visible;

        public:

            // bool faceVisible_front;
            // bool faceVisible_back;
            // bool faceVisible_top;
            // bool faceVisible_bottom;
            // bool faceVisible_left;
            // bool faceVisible_right;

            CubeData(int _type = 1 /*, bool _visible = true*/);
            ~CubeData();

            int getType(){ return type;}
            int getDurability(){ return durability;}
            void setType(int _type);
            void setDurability(int _durability){ durability = _durability;}

            void getStatusFace(int index);

            // bool getVisible(){ return visible;}
            // void setVisible(bool _visible){ visible = _visible;}
    };
}

#endif
