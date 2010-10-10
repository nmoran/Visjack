#ifndef _JACKY_
#define _JACKY_

#include <jack/jack.h>


class Jacky {
	public:
		jack_port_t *input_port;
 		jack_port_t *output_port;
		jack_client_t *client;
		const char **ports;
		
		Jacky(); 
		static int process (jack_nframes_t nframes, void *arg);
	
};


#endif