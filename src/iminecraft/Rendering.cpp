#include <omp.h>
#include "iminecraft/Rendering.hpp"

namespace iminecraft {
	// constructor
	Rendering::Rendering(World& c_world, FreeFlyCamera& c_camera, CharactersGestion& c_charactersGestion)
		: cube(imac2gl3::Cube(1)), skybox(imac2gl3::Skybox(1.f)), planeIntro(iminecraft::PlaneIntro()), cowShape(imac2gl3::NeutralCube(1)), sheepShape(imac2gl3::NeutralCube(2)), pigShape(imac2gl3::NeutralCube(3)), chickenShape(imac2gl3::NeutralCube(0)), monsterShape(imac2gl3::MonsterCube()),
		world(c_world), camera(c_camera), charactersGestion(c_charactersGestion)
	{
		Init();
	}

	void Rendering::Init(){
		InitUniformParams();
		InitTextures();		

    	glEnable(GL_DEPTH_TEST);
    	glEnable(GL_CULL_FACE);

		setPerspective();
	}

	void Rendering::setPerspective(){
		const SDL_VideoInfo* screen = SDL_GetVideoInfo();
		WINDOW_WIDTH = screen->current_w;
		WINDOW_HEIGHT = screen->current_h;
		perspective = glm::perspective(70.0f, WINDOW_WIDTH/ (float) WINDOW_HEIGHT, 0.1f, 1000.0f);
	}

	void Rendering::InitUniformParams(){
	    Program = imac2gl3::loadProgram("shaders/texture.vs.glsl", "shaders/texture.fs.glsl");
	    glUseProgram(Program);

	    projectionMatrixLocation = glGetUniformLocation(Program, "uProjectionMatrix");
		modelViewMatrixLocation = glGetUniformLocation(Program, "uModelViewMatrix");
		normalMatrixLocation = glGetUniformLocation(Program, "uNormalMatrix");

		lightActivatedLocation = glGetUniformLocation(Program, "lightActivated");

		isSkyboxLocation = glGetUniformLocation(Program, "isSkybox");
		nightActivatedLocation = glGetUniformLocation(Program, "nightActivated");
	}

	void Rendering::InitTextures(){  
    	glEnable(GL_BLEND);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		// glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    	TTF_Font *police = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-R.ttf", 20);
    	if(!police){
    		std::cerr << "Erreur lors du chargement de la police." << std::endl;
    		//exit(1);
    	}

    	SDL_Color textColor = {255, 255, 255};
    	// SDL_Color bgColor = {0, 0, 0};

		SDL_Surface *number0 = TTF_RenderText_Blended(police, "0", textColor);
		SDL_Surface *number1 = TTF_RenderText_Blended(police, "1", textColor);
		SDL_Surface *number2 = TTF_RenderText_Blended(police, "2", textColor);
		SDL_Surface *number3 = TTF_RenderText_Blended(police, "3", textColor);
		SDL_Surface *number4 = TTF_RenderText_Blended(police, "4", textColor);
		SDL_Surface *number5 = TTF_RenderText_Blended(police, "5", textColor);
		SDL_Surface *number6 = TTF_RenderText_Blended(police, "6", textColor);
		SDL_Surface *number7 = TTF_RenderText_Blended(police, "7", textColor);
		SDL_Surface *number8 = TTF_RenderText_Blended(police, "8", textColor);
		SDL_Surface *number9 = TTF_RenderText_Blended(police, "9", textColor);
		SDL_Surface *text = TTF_RenderText_Blended(police, "Plus de matériaux de ce type en stock", textColor);

	    textureVector.push_back(TextureTool((char*)"images/logo_imac.png"));
	    textureVector.push_back(TextureTool((char*)"images/texture-terrain.png"));
	    textureVector.push_back(TextureTool((char*)"images/skybox.png"));
	    textureVector.push_back(TextureTool((char*)"images/skin.jpg"));
	    textureVector.push_back(TextureTool((char*)"images/viseur.png"));
	    textureVector.push_back(TextureTool((char*)"images/current.png"));
	    textureVector.push_back(TextureTool((char*)"images/stroke.png"));
	    textureVector.push_back(TextureTool((char*)"images/008-water.png"));
	    textureVector.push_back(TextureTool((char*)"images/012-sable.png"));
	    textureVector.push_back(TextureTool((char*)"images/004-gravat.png"));
	    textureVector.push_back(TextureTool((char*)"images/002-pelouse.png"));
	    textureVector.push_back(TextureTool((char*)"images/lava.png"));
	    textureVector.push_back(TextureTool((char*)"images/017-tronc.png"));
	    textureVector.push_back(TextureTool((char*)"images/018-feuille.png"));
	    textureVector.push_back(TextureTool((char*)"images/torch-icon.png"));
	    textureVector.push_back(TextureTool((char*)"images/AnimauxMineCraft.png"));
	    textureVector.push_back(TextureTool((char*)"images/supermeatboytexture.png"));
	    textureVector.push_back(TextureTool((char*)"images/titre.png"));
	    textureVector.push_back(TextureTool(text));
	    textureVector.push_back(TextureTool(number0));
	    textureVector.push_back(TextureTool(number1));
	    textureVector.push_back(TextureTool(number2));
	    textureVector.push_back(TextureTool(number3));
	    textureVector.push_back(TextureTool(number4));
	    textureVector.push_back(TextureTool(number5));
	    textureVector.push_back(TextureTool(number6));
	    textureVector.push_back(TextureTool(number7));
	    textureVector.push_back(TextureTool(number8));
	    textureVector.push_back(TextureTool(number9));
	    textureVector.push_back(TextureTool((char*)"images/heart.png"));
	    textureVector.push_back(TextureTool((char*)"images/grey_heart.png"));

	    glUniform1i(glGetUniformLocation(Program, "uTexture"), 0);

	    textureVector.push_back(TextureTool((char*)"images/skybox-night.png"));

	    glUniform1i(glGetUniformLocation(Program, "uTexture2"), 1);
	}

	void Rendering::renderWithIntro(bool intro){
		const SDL_VideoInfo* monitor = SDL_GetVideoInfo();
		if(monitor->current_w != WINDOW_WIDTH || monitor->current_h != WINDOW_HEIGHT){
			setPerspective();
		}

	    modelViewStack.set(camera.getViewMatrix());
	    modelViewStack.translate(glm::vec3(0.f, 0.f, 0.f));

	    Material material;
	    material.Ka = glm::vec3(0.1f);
	    material.Kd = glm::vec3(0.8f);
	    material.Ks = glm::vec3(0.005f);
	    material.shininess = 1.0f;

	    MaterialUniform uMaterial = getMaterialLocations("uMaterial", Program);
	    sendMaterial(material, uMaterial);

	    DirectionalLight directionalLight;
	    directionalLight.direction = glm::vec3(camera.getViewMatrix() * glm::vec4(0.05f, -1, 0.1f, 0.f));
	    directionalLight.intensity = glm::vec3(0.8f);

	    DirectionalLightUniform uDirectionalLight = getDirectionalLightLocations("uDirectionalLight", Program);
	    sendDirectionalLight(directionalLight, uDirectionalLight);

	    glUniform1i(nightActivatedLocation, world.getNight());

	    //renderWorld();
    	renderSkybox();
	    renderWorldFromMeshVector();
	    renderCharacter();
	    renderNeutrals();
	    renderMonsters();

	    if(intro){
	    	srand(time(NULL));
	    	//glUniform1i(lightActivatedLocation, 0);
			modelViewStack.push();
				modelViewStack.translate(charactersGestion.getHero().position() + glm::vec3(-128+((rand()%100)*0.01f),-1.5f+((rand()%100)*0.01f),-128+((rand()%100)*0.01f)));
				glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
				glBindTexture(GL_TEXTURE_2D, textureVector.at(1).getTextureID()); // On bind l'objet OpenGL "texture"
					glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
					glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
					planeIntro.draw();
				glBindTexture(GL_TEXTURE_2D, 0);
			modelViewStack.pop();
			//glUniform1i(lightActivatedLocation, 1);
			renderLogo();
	    }else{
	   		renderHUD();
	   	}

	   	world.sendPointLightsToCG(Program, camera.getViewMatrix());

	    // Mise à jour de l'affichage
	    SDL_GL_SwapBuffers();
	}

	void Rendering::renderWorldFromMeshVector(){
		int sizeChunkVector = world.getSizeChunkVector();

		for (int i = 0; i < sizeChunkVector; ++i){
			imac2gl3::GLShapeInstance* shape = world.getMesh(i);			
			int xPos = shape->getXPosition();
			int zPos = shape->getZPosition();

			modelViewStack.push();
				modelViewStack.translate(glm::vec3(xPos*16, 0, zPos*16));
				glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
				glBindTexture(GL_TEXTURE_2D, textureVector.at(1).getTextureID()); // On bind l'objet OpenGL "texture"

					glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewStack.top())));
					glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
					glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
					glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
					shape->draw();
				glBindTexture(GL_TEXTURE_2D, 0);
			modelViewStack.pop();
		}
	}

	// void Rendering::renderWorld(){
	// 	vector<iminecraft::Chunk> chunkVector = world.getChunkVector();
	// 	//imac2gl3::GLShapeInstance cube(imac2gl3::Cube(1.f));
	// 	size_t i = 0;
	// 	int x = 0, y = 0, z = 0, typeOfBlock;
	// 	MatrixStack privateMStack = matrixStack;
	// 	//std::cerr<<privateMStack.top()[0][0]<<" "<<privateMStack.top()[0][1]<<" "<<privateMStack.top()[0][2]<<std::endl;

	// 		for (i = 0; i < chunkVector.size(); ++i){
	// 			int xChunkPosition = chunkVector.at(i).getXPosition();
	// 			int zChunkPosition = chunkVector.at(i).getZPosition();
				
	// 			privateMStack.push();
	// 		        glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
	// 		        glBindTexture(GL_TEXTURE_2D, textureVector.at(0).getTextureID()); // On bind l'objet OpenGL "texture"
	// 		        	//#pragma omp parallel for private(typeOfBlock, privateMStack, x, y, z) shared(chunkVector, i, xChunkPosition, zChunkPosition) ordered
	// 		        	for(x = 0; x < M_WIDTH; ++x){
	// 		            	// Soucis par ici : 0 est en haut, 128 en bas et le chunk va des coordonnées 0 à 64 en y. <= c'est normal pour le 0 à 64, c'est des chunk a moitié remplit
	// 		            	for (y = 0; y < M_HEIGHT; ++y){
	// 		            		for (z = 0; z < M_DEEP; ++z){
	// 		            			typeOfBlock = chunkVector.at(i).getVal(x,y,z); // On récupère le type du block
	// 		            			// on ne va afficher que ceux qui ne sont pas du vide et sont sensé etre visible
	// 		            			if(typeOfBlock > 0 && chunkVector.at(i).getVisible(x,y,z)){
	// 		            				privateMStack.push();
	// 		            					privateMStack.translate(glm::vec3(x + (xChunkPosition*M_WIDTH), y, z + (zChunkPosition*M_DEEP)));
	// 										//#pragma omp critical
	// 		            					{
	// 		            					glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(privateMStack.top()));
	// 		            					cube.draw();
	// 		            					}
	// 				            		privateMStack.pop();
	// 			            		}
	// 		            		}
	// 		            	}
	// 		            }
	// 					//#pragma omp barrier
	// 		        glBindTexture(GL_TEXTURE_2D, 0);
	// 		        privateMStack.pop();
	// 		}
	// }


	void Rendering::renderCharacter(){
		Hero hero = charactersGestion.getHero();
		modelViewStack.push();
			modelViewStack.translate(glm::vec3(	hero.position().x,
												hero.position().y,
												hero.position().z));
			modelViewStack.rotate(hero.direction()*180/M_PI, glm::vec3(0.,1.,0.));
			modelViewStack.scale(glm::vec3(hero.width(),hero.height(),hero.width()));
			glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
			glBindTexture(GL_TEXTURE_2D, textureVector.at(0).getTextureID()); // On bind l'objet OpenGL "texture"
				glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewStack.top())));
				glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
				glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
				glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
				cube.draw();
			glBindTexture(GL_TEXTURE_2D, 0);
		modelViewStack.pop();
		modelViewStack.push();
			//Dessin du bras et d'un cube de l'élément en cours
			glm::vec3 posArm(0.3*camera.getFrontVector().x, 0.3*camera.getFrontVector().y, 0.3*camera.getFrontVector().z);
			posArm += camera.getPosition();
			//std::cerr<<posHUD.x<<","<<posHUD.y<<","<<posHUD.z<<std::endl;
			modelViewStack.translate(posArm);
			modelViewStack.rotate(camera.getAngles().x*180/M_PI, glm::vec3(0.,1.,0.));
			modelViewStack.rotate(camera.getAngles().y*180/M_PI, glm::vec3(-1.,0.,0.));
			int actionAngle = charactersGestion.getHero().getAction();
			actionAngle = (actionAngle < 6) ? actionAngle : (5 - actionAngle%5)%5;
			modelViewStack.rotate(-20. + actionAngle*2, glm::vec3(0.,0.,1.));
			modelViewStack.rotate(20. + actionAngle*8, glm::vec3(-1.,0.,0.));
			modelViewStack.rotate(-actionAngle*4, glm::vec3(0.,1.,0.));
			modelViewStack.translate(glm::vec3(0.05, 0.15, 0.05));
			modelViewStack.push();
				modelViewStack.scale(glm::vec3(hero.width()*0.2, hero.height()*0.3, hero.width()*0.2));
				glBindTexture(GL_TEXTURE_2D, textureVector.at(3).getTextureID()); // On bind l'objet OpenGL "texture"
					normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewStack.top())));
					glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
					glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
					glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
					cube.draw();
				glBindTexture(GL_TEXTURE_2D, 0);
			modelViewStack.pop();
				// Dessin de l'élément en cours d'utilisation
			size_t typeOfBlock = charactersGestion.getHero().getFromInventory(hero.currentIndex());
			if(typeOfBlock > 0){
				modelViewStack.push();
					modelViewStack.translate(glm::vec3(0.03, -0.1, 0.05));
					modelViewStack.rotate(20., glm::vec3(0.,0.,1.));
					modelViewStack.rotate(-20., glm::vec3(-1.,0.,0.));
					modelViewStack.scale(glm::vec3(hero.width()*0.25, hero.width()*0.25, hero.width()*0.25));
					glBindTexture(GL_TEXTURE_2D, textureVector.at(1).getTextureID()); // On bind l'objet OpenGL "texture"
						normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewStack.top())));
						glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
						glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
						glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));

						imac2gl3::GLShapeInstance cubeInTheHand(imac2gl3::Cube((int)typeOfBlock));
						cubeInTheHand.draw();
					glBindTexture(GL_TEXTURE_2D, 0);
				modelViewStack.pop();
			}
		modelViewStack.pop();
	}


	void Rendering::renderNeutrals(){
		for(size_t i = 0; i < charactersGestion.getNumberOfNeutrals(); ++i){
			Neutral tempNeutral = charactersGestion.getNeutral(i);
			modelViewStack.push();
				modelViewStack.translate(glm::vec3(
							tempNeutral.position().x,
							tempNeutral.position().y,
							tempNeutral.position().z));
				modelViewStack.rotate(tempNeutral.direction()*180/M_PI, glm::vec3(0.,1.,0.));
				modelViewStack.scale(glm::vec3(tempNeutral.width(),tempNeutral.height(),tempNeutral.width()));

				glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
					glBindTexture(GL_TEXTURE_2D, textureVector.at(15).getTextureID()); // On bind l'objet OpenGL "texture"
						glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewStack.top())));
						glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
						glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
						glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));

						switch(tempNeutral.type()){
							case cow:
								cowShape.draw();
								break;
							case sheep:
								sheepShape.draw();
								break;
							case pig:
								pigShape.draw();
								break;
							case chicken:
								chickenShape.draw();
								break;
							default:
								sheepShape.draw();
								break;
						}
						
					glBindTexture(GL_TEXTURE_2D, 0);
			modelViewStack.pop();
		}
	}



	void Rendering::renderMonsters(){
		for(size_t i = 0; i < charactersGestion.getNumberOfMonsters(); ++i){
			Monster tempMonster = charactersGestion.getMonster(i);
			modelViewStack.push();
				modelViewStack.translate(glm::vec3(
							tempMonster.position().x,
							tempMonster.position().y,
							tempMonster.position().z));
				modelViewStack.rotate(tempMonster.direction()*180/M_PI, glm::vec3(0.,1.,0.));
				modelViewStack.scale(glm::vec3(tempMonster.width(),tempMonster.height(),tempMonster.width()));
				glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
					glBindTexture(GL_TEXTURE_2D, textureVector.at(16).getTextureID()); // On bind l'objet OpenGL "texture"
						glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewStack.top())));
						glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
						glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
						glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
						monsterShape.draw();
					glBindTexture(GL_TEXTURE_2D, 0);
			modelViewStack.pop();
		}
	}

	void Rendering::renderSkybox(){
		glUniform1i(lightActivatedLocation, 0);
		glUniform1i(isSkyboxLocation, 1);
	    	glCullFace(GL_FRONT);
		    	modelViewStack.push();
		    	    modelViewStack.translate(charactersGestion.getHero().position());
		        	modelViewStack.scale(glm::vec3(1000.f));
					glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
					glBindTexture(GL_TEXTURE_2D, textureVector.at(2).getTextureID()); // On bind l'objet OpenGL "texture"

					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, textureVector.at(31).getTextureID());

					glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
					glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
					skybox.draw();

					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, 0);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, 0);
				modelViewStack.pop();
			glCullFace(GL_BACK);
		glUniform1i(isSkyboxLocation, 0);
		glUniform1i(lightActivatedLocation, 1);
	}
	
	void Rendering::renderLogo(){
		glUniform1i(lightActivatedLocation, 0);
		GLShapeInstance maFace(imac2gl3::Face(1.f));
		modelViewStack.push();
			glm::vec3 posHUD(0.2*camera.getFrontVector().x, 0.2*camera.getFrontVector().y, 0.2*camera.getFrontVector().z);
			posHUD += camera.getPosition();
			//std::cerr<<posHUD.x<<","<<posHUD.y<<","<<posHUD.z<<std::endl;
			modelViewStack.translate(posHUD);
			modelViewStack.rotate(camera.getAngles().x*180/M_PI, glm::vec3(0.,1.,0.));
			modelViewStack.rotate(camera.getAngles().y*180/M_PI, glm::vec3(-1.,0.,0.));
			modelViewStack.scale(glm::vec3(.2, .2, 1.));
			modelViewStack.translate(glm::vec3(-0.5, -0.5, 0.));

            glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
            glBindTexture(GL_TEXTURE_2D, textureVector.at(17).getTextureID());
                glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
                glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
                maFace.draw();
            glBindTexture(GL_TEXTURE_2D, 0);

		modelViewStack.pop();
		glUniform1i(lightActivatedLocation, 1);
	}

	void Rendering::renderHUD(){
		glUniform1i(lightActivatedLocation, 0);
		GLShapeInstance maFace(imac2gl3::Face(1.f));
		modelViewStack.push();
			glm::vec3 posHUD(0.2*camera.getFrontVector().x, 0.2*camera.getFrontVector().y, 0.2*camera.getFrontVector().z);
			posHUD += camera.getPosition();
			//std::cerr<<posHUD.x<<","<<posHUD.y<<","<<posHUD.z<<std::endl;
			modelViewStack.translate(posHUD);
			modelViewStack.rotate(camera.getAngles().x*180/M_PI, glm::vec3(0.,1.,0.));
			modelViewStack.rotate(camera.getAngles().y*180/M_PI, glm::vec3(-1.,0.,0.));
			modelViewStack.scale(glm::vec3(.02, .02, 1.));
			
            // Le viseur
			modelViewStack.push();
			modelViewStack.translate(glm::vec3(-0.5, -0.5, 0.));
            glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
            glBindTexture(GL_TEXTURE_2D, textureVector.at(4).getTextureID());
                glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
                glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
                maFace.draw();
            glBindTexture(GL_TEXTURE_2D, 0);
            modelViewStack.pop();
            
            //Life
            modelViewStack.push();
            modelViewStack.translate(glm::vec3(-2.5, 5.5, 0.));
            modelViewStack.scale(glm::vec3(0.5, 0.5, 1.));
            for(int life=0 ; life < charactersGestion.getHero().life(); ++life){
            	modelViewStack.push();
            	modelViewStack.translate(glm::vec3(life, 0., 0.));
				glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
				glBindTexture(GL_TEXTURE_2D, textureVector.at(29).getTextureID());
					glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
					glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
					maFace.draw();
				glBindTexture(GL_TEXTURE_2D, 0);
				modelViewStack.pop();
            }
            for(int life=charactersGestion.getHero().life() ; life < charactersGestion.getHero().maxLife(); ++life){
            	modelViewStack.push();
            	modelViewStack.translate(glm::vec3(life, 0., 0.));
				glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
				glBindTexture(GL_TEXTURE_2D, textureVector.at(30).getTextureID());
					glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
					glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
					maFace.draw();
				glBindTexture(GL_TEXTURE_2D, 0);
				modelViewStack.pop();
            }
            modelViewStack.pop();

            //Inventory
			modelViewStack.translate(glm::vec3(-5., 6., 0.));
			for(size_t i=0; i<10; i++){
				modelViewStack.push();
				size_t tex = charactersGestion.getHero().getFromInventory(i);
				if(tex >= 0){
					modelViewStack.translate(glm::vec3(float(i), 0., 0.));
					//glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
					glBindTexture(GL_TEXTURE_2D, textureVector.at(tex+6).getTextureID());
						glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
						glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
						maFace.draw();
					glBindTexture(GL_TEXTURE_2D, 0);

					modelViewStack.translate(glm::vec3(0., 0., -0.0002));
					//écriture du nombre de cubes en stock
					int nbStock = charactersGestion.getHero().getQuantityOf(i);
					int j = 1;

					//std::cerr<<( pow(10.0, 1) <= nbStock )<<std::endl;
					while((int)pow(10.0, j-1) <= nbStock && j < 5){
						modelViewStack.push();
						int unity = (nbStock/(int)pow(10.0, j-1)) % 10;
						//std::cerr<<unity<<std::endl;
						/*while(unity > pow(10.0, j) - 1)
							unity = unity%10;*/
						modelViewStack.scale(glm::vec3(0.12, 0.3, 0.));
						modelViewStack.translate(glm::vec3(float(1-j) + 6., 0.25, 0.));
						glBindTexture(GL_TEXTURE_2D, textureVector.at(unity+19).getTextureID());
							glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
							glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
							maFace.draw();
						glBindTexture(GL_TEXTURE_2D, 0);
						++j;
						modelViewStack.pop();
					}

					modelViewStack.translate(glm::vec3(0., 0., 0.0001));
					if(charactersGestion.getHero().currentIndex() == i){
						//glActiveTexture(GL_TEXTURE0); // Unité de texture 0, valeur qu'on à envoyé pour l'uniforme
						glBindTexture(GL_TEXTURE_2D, textureVector.at(5).getTextureID());
							glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(perspective));
							glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewStack.top()));
							maFace.draw();
						glBindTexture(GL_TEXTURE_2D, 0);
					}

				}
				modelViewStack.pop();
			}
		modelViewStack.pop();
		glUniform1i(lightActivatedLocation, 1);
	}

	// destructor
	Rendering::~Rendering(){		
	}
}
