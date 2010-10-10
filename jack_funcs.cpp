#include "engine.h"

int process (jack_nframes_t nframes, void *arg)
 {
	//jack_default_audio_sample_t *out = (jack_default_audio_sample_t *) jack_port_get_buffer (output_port, nframes);
	jack_default_audio_sample_t *in = (jack_default_audio_sample_t *) jack_port_get_buffer (input_port, nframes);
	
	int start = (WINDOW_SIZE-1+current_window)*FRAME_SIZE;
	int start2 = (current_window-1)*FRAME_SIZE;
	for ( int i = 0 ; i < nframes ; i++ ) {
		//data_array[i] = (float)out[(pos+i)%DATA_SIZE];
		fftw_in[start+i][0] = (double)in[i];
		if ( current_window > 0 ) {
			fftw_in[start2+i][0] = (double)in[i];
		}
	}
	//pos = (pos + nframes)%DATA_SIZE; 
	
	//printf("Number of frames: %d.\n", (int)nframes);
	
	//memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);
	current_window = (current_window + 1)%WINDOW_SIZE; 
	
	return 0;      
 }
 
 /**
  * This is the shutdown callback for this JACK application.
  * It is called by JACK if the server ever shuts down or
  * decides to disconnect the client.
  */
 void jack_shutdown (void *arg)
 {
         exit (1);
 }
 