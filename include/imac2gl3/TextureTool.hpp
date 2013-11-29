#ifndef _IMAC2GL3_TEXTURETOOL_HPP_
#define _IMAC2GL3_TEXTURETOOL_HPP_

#include <SDL/SDL_image.h>
#include <GL/glew.h>

class TextureTool{
    public:
        TextureTool();
        TextureTool(char* pathImg);
        TextureTool(SDL_Surface* surface);

        // move semantics
        TextureTool(TextureTool&& text)
            : texture(text.texture) {
                text.texture = 0;
        };

        TextureTool& operator=(TextureTool&& text){
            texture = text.texture;
            text.texture = 0;
            return *this;
        };
        
        ~TextureTool();

        GLenum getFormatRGB(SDL_Surface* textureImage);
        void PrepareTexture(char* pathImg);
        void PrepareTexture(SDL_Surface* surface);

        GLuint getTextureID();        
    private:
        SDL_Surface *textureImage;
        GLuint texture;
};

#endif
