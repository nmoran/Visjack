#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "model.h" 
#include "util.h"
#include "camera.h"
#include "ttorus.h"
#include <complex>
#include <fftw3.h>

#include <jack/jack.h>

#define FRAME_SIZE 512 // number of samples in a frame.
#define WINDOW_SIZE 16 //number of frames in a window.
#define SAMPLE_RATE 48000 //number of samples per second.

#define DATA_SIZE 16384.0
#define BINS 30 //number of bins for histogram visualisation.
#define FPS 60.0
 
extern jack_port_t *input_port;
extern jack_port_t *output_port;

extern float *data_array;
extern int pos;

extern fftw_complex *fftw_in, *fftw_in_data, *fftw_out, *window;
extern fftw_plan *fftw_p, fftw_plan_data;
extern float **height_map;
extern int current_window;
 
 /**
  * The process callback for this JACK application.
  * It is called by JACK at the appropriate times.
  */
int process (jack_nframes_t nframes, void *arg);
void jack_shutdown (void *arg);

class CEngine {

	CModel *mymodel;
	CTtorus *mytorus;
	Ccamera *mycamera;
    	SDL_VideoInfo* info ;
    	int width ;
    	int height;
    	int bpp;
    	int flags;
    	string model_name ;

	unsigned int last_tick_count ; 
	unsigned int current_tick_count ; 
	unsigned int diff_ticks;
	unsigned int frame_count ;
	unsigned int last_fps ; 

	public:
	CEngine( int argc, char* argv[]   );
	void quit( int code );
	void handle_key_down( SDL_keysym* keysym );
	void handle_key_up( SDL_keysym* keysym );
	void process_events( void );
	void draw_screen( void );
	void setup_opengl( int width, int height );
	void start();


};

#endif

