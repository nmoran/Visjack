COMPILE = g++ -c -g `sdl-config --cflags` -I${HOME}/local/SDL_image/include  
LINKER = g++ -g  -framework opengl -framework Cocoa `sdl-config --libs` -L${HOME}/local/SDL_image/lib -lSDL_image -ljack -framework CoreAudio -lfftw3

model_viewer : model_viewer.o model.o camera.o engine.o ttorus.o jack_funcs.o
	${LINKER} -o model_viewer model_viewer.o model.o camera.o engine.o ttorus.o jack_funcs.o

jack_funcs.o : jack_funcs.cpp engine.h
	${COMPILE}  jack_funcs.cpp 

model.o : model.cpp model.h 
	${COMPILE}  model.cpp

model_viewer.o : model_viewer.cpp engine.h
	${COMPILE} model_viewer.cpp

camera.o : camera.cpp camera.h util.h 
	${COMPILE} camera.cpp

engine.o : engine.cpp engine.h util.h 
	${COMPILE} engine.cpp

ttorus.o : ttorus.cpp ttorus.h util.h
	${COMPILE} ttorus.cpp

texture.o : texture.cpp texture.h util.h
	${COMPILE} texture.cpp

.PHONY: clean

clean: 
	rm *.o model_viewer

.PHONY: doc

doc: 
	cd doc
	doxygen doxygen.conf
