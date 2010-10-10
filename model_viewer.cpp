/*--------------------
*
* Name : model_viewer.cpp
* Author : Niall Moran
* Licence : GPL
*
--------------------*/

#include "engine.h"

using namespace std;

jack_port_t *input_port;
jack_port_t *output_port;
float *data_array;
int pos;
fftw_complex *fftw_in, *fftw_out, *fftw_in_data, *fftw_data, *window;
fftw_plan *fftw_p, fftw_plan_data;
float **height_map;
int current_window;


int main(int argc, char*argv[]);


int main( int argc, char* argv[] )
{
	jack_client_t *client;
	const char **ports;
	
	char name[] = "jackvis";
	/* try to become a client of the JACK server */
	
	if ((client = jack_client_new (name)) == 0) {
		fprintf (stderr, "jack server not running?\n");
		return 1;
	}
	
	data_array = (float*)malloc(sizeof(float)*DATA_SIZE);
	height_map = (float**)malloc(sizeof(float*)*BINS);
	for ( int i = 0 ; i < BINS ; i++ ) {
		height_map[i] = (float*)malloc(sizeof(float)*BINS);
		for ( int j = 0 ; j < BINS ; j++ ) {
			height_map[i][j] = 0.0;
		}
	}
	
	fftw_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FRAME_SIZE*WINDOW_SIZE*2);
	for ( int i = 0 ; i < FRAME_SIZE*WINDOW_SIZE*2 ; i++ ) {
		fftw_in[i][0] = 0.0; fftw_in[i][1] = 0.0;
	}
	fftw_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FRAME_SIZE*WINDOW_SIZE);
	for ( int i = 0 ; i < FRAME_SIZE*WINDOW_SIZE ; i++ ) {
		fftw_out[i][0] = 0.0; fftw_out[i][1] = 0.0;
	}
	fftw_p = (fftw_plan*)malloc(sizeof(fftw_plan)*WINDOW_SIZE);
	for ( int i = 0 ; i < WINDOW_SIZE ; i++ ) {
		fftw_p[i] = fftw_plan_dft_1d(FRAME_SIZE*WINDOW_SIZE, &(fftw_in[i*FRAME_SIZE]), fftw_out, FFTW_FORWARD, FFTW_ESTIMATE);
	}
	current_window = 0;
	
	
	
	fftw_in_data = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FRAME_SIZE*WINDOW_SIZE);
	for ( int i = 0 ; i < FRAME_SIZE*WINDOW_SIZE ; i++ ) {
		fftw_in_data[i][0] = 0.0; fftw_in[i][1] = 0.0;
	}
	
	window = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FRAME_SIZE*WINDOW_SIZE);
	for ( int i = 0 ; i < FRAME_SIZE*WINDOW_SIZE ; i++ ) {
		window[i][0] = 0.54 - 0.46 * cos((2.0*PI*((double)i))/((double)(FRAME_SIZE*WINDOW_SIZE-1))); 
	}

	fftw_plan_data = fftw_plan_dft_1d(FRAME_SIZE*WINDOW_SIZE, fftw_in_data, fftw_out, FFTW_FORWARD, FFTW_MEASURE);
	
	for ( int i = 0 ; i < DATA_SIZE ; i++ ) { 
		data_array[i] = 0.0;
	}
	pos = 0;
	/* tell the JACK server to call `process()' whenever
	there is work to be done.
	*/
	
	
	
	jack_set_process_callback (client, process, 0);
	
	/* tell the JACK server to call `jack_shutdown()' if
	it ever shuts down, either entirely, or if it
	just decides to stop calling us.
	*/
	
	jack_on_shutdown (client, jack_shutdown, 0);
	
	/* display the current sample rate. 
	*/
	
	//printf ("engine sample rate: %" PRIu32 "\n", jack_get_sample_rate (client));
	
	/* create two ports */
	
	input_port = jack_port_register (client, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
	output_port = jack_port_register (client, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
	
	/* tell the JACK server that we are ready to roll */
	
	if (jack_activate (client)) {
	fprintf (stderr, "cannot activate client");
	return 1;
	}
	
	/* connect the ports. Note: you can't do this before
	the client is activated, because we can't allow
	connections to be made to clients that aren't
	running.
	*/
	
	//if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput)) == NULL) {
	if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsOutput)) == NULL) {
	fprintf(stderr, "Cannot find any physical capture ports\n");
	exit(1);
	}
	
	int j = 0;
	while ( ports[j] != NULL ) {
		if (jack_connect (client, ports[j], jack_port_name (input_port))) {
		fprintf (stderr, "cannot connect input ports\n");
		}
		j++;
	}
	
	free (ports);
	
	/*if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsPhysical|JackPortIsInput)) == NULL) {
	fprintf(stderr, "Cannot find any physical playback ports\n");
	exit(1);
	}*/
	
	
	/*if (jack_connect (client, jack_port_name (output_port), ports[i])) {
		fprintf (stderr, "cannot connect output ports\n");
	}*/
	
	

	CEngine *myengine = new CEngine(argc, argv);
	myengine->start();
	
	//free (ports);
	
	free(data_array);
	for ( int i = 0 ; i < WINDOW_SIZE; i++ ) {
		fftw_destroy_plan(fftw_p[i]);
	}
	free(fftw_p);
    fftw_free(fftw_in); fftw_free(fftw_out);
    for ( int i = 0 ; i < BINS ; i++ ) {
    	free(height_map[i]);
    }
    free(height_map);
	jack_client_close (client);


	return 0 ;
}
