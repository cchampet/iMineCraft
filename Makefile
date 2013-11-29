CC = g++
CFLAGS = -Wall -ansi -pedantic -O2 -I include -I /usr/include/SDL/ -Wno-long-long -fno-show-column -std=c++0x 
MPFLAGS = -fopenmp -lstdc++
#CFLAGS += -Wno-unknown-pragmas
LDFLAGS = -lSDL -lGL -lSDL_image -lSDL_mixer -lSDL_ttf -lnoise

LIB_GTEST=-lgtest -lgtest_main -lpthread
TEST_EXT=.test

LIBS=lib/.libs

FILES_PATH=files
TEST_PATH=gtest
SRC_PATH=src
BIN_PATH=bin
OBJ_PATH=obj
MUSIC_PATH=music
LIB_PATH=-L $(LIBS)

DIRNAME= $(shell basename $$PWD)
BACKUP= $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)

EXEC = iMineCraft

SRC_FILES = $(shell find $(SRC_PATH) -mindepth 2 -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRC_FILES))

SRC_TEST = $(shell find $(TEST_PATH) -type f -name '*.cpp')
OBJ_TEST = $(patsubst $(TEST_PATH)/%.cpp, $(OBJ_PATH)/$(TEST_PATH)/%.o, $(SRC_TEST))


all: /usr/include/SDL/SDL_ttf.h /usr/include/SDL/SDL_mixer.h /usr/include/libnoise/noise.h $(FILES_PATH) $(BIN_PATH) $(MUSIC_PATH) $(BIN_PATH)/$(EXEC)

$(BIN_PATH)/$(EXEC): $(OBJ_FILES) $(OBJ_PATH)/glew-1.9/glew.o $(OBJ_PATH)/main.o
	$(CC) -o $@ $^ $(LDFLAGS) $(MPFLAGS)

$(OBJ_PATH)/glew-1.9/glew.o: $(SRC_PATH)/glew-1.9/glew.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $(MPFLAGS) $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $(MPFLAGS) $^


/usr/include/libnoise/noise.h :
	@echo ""
	@echo "This programm needs the library Libnoise-dev which is not installed on your computer yet, we will install it for you :"
	sudo apt-get install libnoise-dev


/usr/include/SDL/SDL_mixer.h :
	@echo ""
	@echo "This programm needs the library SDL_mixer which is not installed on your computer yet, we will install it for you :"
	sudo apt-get install libsdl-mixer1.2-dev
	
	
/usr/include/SDL/SDL_ttf.h :
	@echo ""
	@echo "This programm needs the library SDL_ttf which is not installed on your computer yet, we will install it for you :"
	sudo apt-get install libsdl-ttf2.0-0 libsdl-ttf2.0-dev	
	
	
$(BIN_PATH):
	mkdir $(BIN_PATH)
	
$(FILES_PATH):
	mkdir $(FILES_PATH)
	
$(MUSIC_PATH):
	mkdir $(MUSIC_PATH)

	
test: $(BIN_PATH) $(BIN_PATH)/$(EXEC)$(TEST_EXT)
	export LD_LIBRARY_PATH=$(LIBS) && $(BIN_PATH)/$(EXEC)$(TEST_EXT)

$(BIN_PATH)/$(EXEC)$(TEST_EXT): $(OBJ_FILES) $(OBJ_PATH)/glew-1.9/glew.o $(OBJ_TEST)
	$(CC) -o $@ $^ $(LDFLAGS) $(MPFLAGS) $(LIB_GTEST) $(LIB_PATH)
	
$(OBJ_PATH)/$(TEST_PATH)/%.o: $(TEST_PATH)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $(MPFLAGS) $^


unsave:
	rm $(FILES_PATH)/*

clean:
	rm $(OBJ_FILES)

reset:
	rm -Rf $(BIN_PATH) $(OBJ_PATH) $(FILES_PATH)
	
tar : cleanall
	cd .. && mkdir music_tmp && mv -f $(DIRNAME)/music/* ./music_tmp/
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)
	mv -f ../music_tmp/* ./music/
	rmdir ../music_tmp
