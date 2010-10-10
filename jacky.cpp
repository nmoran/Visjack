#include "jacky.h"

Jacky::Jacky(char *name) { 

	 /* try to become a client of the JACK server */

	 if ((client = jack_client_new   (name) == 0) {
		fprintf (stderr, "jack server not running?\n");
		return 1;
	 }

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

	 printf ("engine sample rate: %" PRIu32 "\n",
			 jack_get_sample_rate (client));

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

	 if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput)) == NULL) {
			 fprintf(stderr, "Cannot find any physical capture ports\n");
			 exit(1);
	 }

	 if (jack_connect (client, ports[0], jack_port_name (input_port))) {
			 fprintf (stderr, "cannot connect input ports\n");
	 }

	 free (ports);
	 
	 if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsPhysical|JackPortIsInput)) == NULL) {
			 fprintf(stderr, "Cannot find any physical playback ports\n");
			 exit(1);
	 }

	 if (jack_connect (client, jack_port_name (output_port), ports[0])) {
			 fprintf (stderr, "cannot connect output ports\n");
	 }

	 free (ports);

	 /* Since this is just a toy, run for a few seconds, then finish */

	 //sleep (10);
	 for(;;)
		sleep (1);
	 
	 jack_client_close (client);
	 exit (0);
}