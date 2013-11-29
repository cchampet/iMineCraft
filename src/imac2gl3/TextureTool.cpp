#include "../../include/imac2gl3/TextureTool.hpp"

// Constructeur
TextureTool::TextureTool(){
	glGenTextures( 1, &texture );
}

TextureTool::TextureTool(char* pathImg){
	glGenTextures(1, &texture );
	PrepareTexture(pathImg);
}

TextureTool::TextureTool(SDL_Surface* surface){
	glGenTextures(1, &texture );
	PrepareTexture(surface);
}

GLenum TextureTool::getFormatRGB(SDL_Surface* textureImage){
	if(textureImage->format->BytesPerPixel == 1)
        return GL_RED; // niveau de gris
    else if(textureImage->format->BytesPerPixel == 3)
    	return GL_RGB; // RGB
    else
    	return GL_RGBA; // avec transparence
}


void TextureTool::PrepareTexture(char* pathImg){
	textureImage = IMG_Load(pathImg);

	glBindTexture( GL_TEXTURE_2D, texture );// select our current texture

		glTexImage2D(GL_TEXTURE_2D, // cible (GL_TEXTURE_2D)
	                    0, // Niveau de resolution lorsqu'on utilise le mipmapping (0 pour nous)
	                    GL_RGBA, // Format à utiliser sur la carte graphique (GL_RGBA)
	                    textureImage->w, // Largeur de l'image
	                    textureImage->h, // Hauteur de l'image
	                    0, // Mettre 0
	                    getFormatRGB(textureImage), // Format des données que l'on envoi (voir plus bas)
	                    GL_UNSIGNED_BYTE, // Type des données que l'on envoi (voir plus bas)
	                    textureImage->pixels); // Pointeur vers les données (voir plus bas)

	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_LINEAR);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_LINEAR);

	glBindTexture( GL_TEXTURE_2D, 0);

	SDL_FreeSurface(textureImage); // free SDL_Surface
}

void TextureTool::PrepareTexture(SDL_Surface* surface){
	textureImage = surface;

	glBindTexture( GL_TEXTURE_2D, texture );// select our current texture

		glTexImage2D(GL_TEXTURE_2D, // cible (GL_TEXTURE_2D)
	                    0, // Niveau de resolution lorsqu'on utilise le mipmapping (0 pour nous)
	                    GL_RGBA, // Format à utiliser sur la carte graphique (GL_RGBA)
	                    textureImage->w, // Largeur de l'image
	                    textureImage->h, // Hauteur de l'image
	                    0, // Mettre 0
	                    getFormatRGB(textureImage), // Format des données que l'on envoi (voir plus bas)
	                    GL_UNSIGNED_BYTE, // Type des données que l'on envoi (voir plus bas)
	                    textureImage->pixels); // Pointeur vers les données (voir plus bas)

	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_LINEAR);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_LINEAR);

	glBindTexture( GL_TEXTURE_2D, 0);

	SDL_FreeSurface(textureImage); // free SDL_Surface
}

GLuint TextureTool::getTextureID(){
	return texture;
}

// Destructeur
TextureTool::~TextureTool(){
	if(texture != 0)
		glDeleteTextures( 1, &texture );
}

