/*--------------------
*
* Name : engine.cpp 
* Author : Niall Moran
* Licence : GPL
*
--------------------*/

#include "engine.h"
#include <stdio.h>


using namespace std;


void CEngine::quit( int code )
{
   SDL_Quit( );
   exit( code );
}

void CEngine::handle_key_down( SDL_keysym* keysym )
{
   switch( keysym->sym ) {
    case SDLK_ESCAPE:
        quit( 0 );
        break;
    case SDLK_UP:
    case SDLK_w:
	mycamera->move_forward(1.0);
        break;
    case SDLK_DOWN:
    case SDLK_s:
	mycamera->move_back(1.0);
        break;
    case SDLK_LEFT:
    case SDLK_a:
	mycamera->strafe_left(1.0);
        break;
    case SDLK_RIGHT:
    case SDLK_d:
	mycamera->strafe_right(1.0);
        break;
    case SDLK_o:
	mycamera->move_up(1.0);
        break;
    case SDLK_p:
	mycamera->move_down(1.0);
        break;	

    case SDLK_SPACE:
        break;
   default:
        break;
    }
}

void CEngine::handle_key_up( SDL_keysym* keysym )
{
   switch( keysym->sym ) {
    case SDLK_UP:
    case SDLK_DOWN:
    case SDLK_w:
    case SDLK_s:
	mycamera->stop_move_forward_back();
        break;
    case SDLK_LEFT:
    case SDLK_RIGHT:
    case SDLK_a:
    case SDLK_d:
	mycamera->stop_strafe();
        break;
   case SDLK_o:
    case SDLK_p:
	mycamera->stop_up_down();
        break;	
   default:
        break;
    }
}

void CEngine::process_events( void )
{
    /* Our SDL event placeholder. */
    SDL_Event event;

    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {

        switch( event.type ) {
	/*case SDL_MOUSEMOTION:
//	     printf("Mouse moved by %d,%d to (%d,%d)\n", 
                     //  event.motion.xrel, event.motion.yrel,
                      // event.motion.x, event.motion.y);
	     if ( !(event.motion.x == 100 && event.motion.y == 100) ) {
		if ( ( event.motion.xrel > 0 || event.motion.xrel < 0 ) && ( event.motion.xrel != event.motion.x && event.motion.yrel != event.motion.y) ) {
			mycamera->look_left_right(-(float)event.motion.xrel *  (float)diff_ticks / 1000.0 );	
		}
	     	if ( ( event.motion.yrel > 0 || event.motion.yrel < 0 ) && ( event.motion.xrel != event.motion.x && event.motion.yrel != event.motion.y) ) {
			mycamera->look_up_down((float)event.motion.yrel * (float)diff_ticks / 1000.0 );	
	     	}
		SDL_WarpMouse(100,100);
	     } 
             break;*/
    case SDL_KEYDOWN:
            // Handle key presses. 
            handle_key_down( &event.key.keysym );
            break;
	case SDL_KEYUP:
            // Handle key presses. 
            handle_key_up( &event.key.keysym );
            break;

        case SDL_QUIT:
            /* Handle quit requests (like Ctrl-c). */
            quit( 0 );
            break;
        }

    }

}

void CEngine::draw_screen( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    float rms;

    mycamera->advance_camera((float)diff_ticks/1000.0);
    mycamera->set_modelview();

  	
  	glColor3f(0.5,0.8,0.1);
  
    glPushMatrix();

    //draw axis
    glColor4f(0.0, 1.0, 0.0 , 1.0);
    glBegin(GL_LINES);
		glVertex3f(-100.0,0.0,0.0);
        glVertex3f(100.0,0.0,0.0);

		glVertex3f(0.0, -100.0, 0.0);
        glVertex3f(0.0, 100.0,0.0);

		glVertex3f(0.0,0.0,-100.0);
        glVertex3f(0.0,0.0,100.0);
    glEnd();
    
    rms = 0 ;
	for ( int i = current_window*FRAME_SIZE ; i < current_window*FRAME_SIZE + FRAME_SIZE*WINDOW_SIZE ; i++ ) {
		rms += fftw_in[i][0];
	}
    
    for ( int i = 0 ; i < FRAME_SIZE*WINDOW_SIZE ; i++ ) {
    	fftw_in_data[i][0] = fftw_in[current_window*FRAME_SIZE + i][0] * window[i][0] ;
    }
    
    //get the fourier transform of the signal.
    fftw_execute(fftw_plan_data);
    
    /*for ( int i = 0 ; i < BINS - 1 ; i++ ) {
    	for ( int j = 0 ; j < BINS ; j++ ) {
    		height_map[i+1][j] = height_map[i][j];
    	}
    }
    for ( int i = 0 ; i < BINS ; i++ ) {
    	height_map[0][i] = 0.0;
    }
    
    int range;
    for ( int i = 0 ; i < DATA_SIZE ; i++ ) {
    	range = i / ( DATA_SIZE / BINS ) ;
    	height_map[0][range] += sqrt(fftw_out[i][0]*fftw_out[i][0] + fftw_out[i][1]*fftw_out[i][1])/(double)DATA_SIZE;
    }*/
   
   	/*glBegin(GL_QUADS);
    for ( int x = 0 ; x < BINS ; x++ ) {
    	for ( int y = 0 ; y < BINS ; y++ ) {
    		glNormal3f(0.0,0.0,1.0);
    		glVertex3f((float)(-BINS/2 + x), (float)(BINS/2 - y),height_map[x][y]);
    		glVertex3f((float)(-BINS/2 + x)+1.0, (float)(BINS/2 - y),height_map[x][y]);
    		glVertex3f((float)(-BINS/2 + x)+1.0, (float)(BINS/2 - y)-1.0,height_map[x][y]);
    		glVertex3f((float)(-BINS/2 + x), (float)(BINS/2 - y)-1.0,height_map[x][y]);*/
    		/*glVertex3f((float)(-BINS/2 + x), (float)(BINS/2 - y),0.0);
    		glVertex3f((float)(-BINS/2 + x)+1.0, (float)(BINS/2 - y),0.0);
    		glVertex3f((float)(-BINS/2 + x)+1.0, (float)(BINS/2 - y)-1.0,0.0);
    		glVertex3f((float)(-BINS/2 + x), (float)(BINS/2 - y)-1.0,0.0);*/
    	/*}
    }
    glEnd();*/
    
    float pos1, pos2;
    glBegin(GL_QUADS);
    for ( int i = 0 ; i < WINDOW_SIZE*FRAME_SIZE/2 ;  i++ ) {
    	
    	
    	pos1 = (float)log((double)i+1)*5.0;
    	pos2 = pos1 + 0.1;
    	//pos1 = (((double)i)/DATA_SIZE)*20.0;
       	//pos2 = pos1 + 20.0/DATA_SIZE;
    	//printf("Position 1 and 2: %f, %f.\n", pos1,pos2);
    	glVertex3f(pos1,0.0,0.0);
    	glVertex3f(pos2,0.0,0.0);
    	//glVertex3f((float)((i+1)*0.01),0.0,data_array[i]*5.0);
    	//glVertex3f((float)((0+i)*0.01),0.0,data_array[i]*5.0);
    	glVertex3f(pos2,0.0,fftw_out[i][0]/(float)DATA_SIZE*100.0);
    	glVertex3f(pos1,0.0,fftw_out[i][0]/(float)DATA_SIZE*100.0);
    	
    	//glVertex3f(pos2,0.0,window[i][0]*20.0);
    	//glVertex3f(pos1,0.0,window[i][0]*20.0);
    }
	pos1 = (float)log(((double)(WINDOW_SIZE*FRAME_SIZE))/2.0)*5.0;
	pos2 = pos1 + 0.1;
	glVertex3f(pos1,0.0,0.0);
	glVertex3f(pos2,0.0,0.0);
	glVertex3f(pos2,0.0,2.0);
	glVertex3f(pos1,0.0,2.0);
	
	pos1 = (float)log(((double)(WINDOW_SIZE*FRAME_SIZE))/4.0)*5.0;
	pos2 = pos1 + 0.1;
	glVertex3f(pos1,0.0,0.0);
	glVertex3f(pos2,0.0,0.0);
	glVertex3f(pos2,0.0,2.0);
	glVertex3f(pos1,0.0,2.0);
	
	pos1 = (float)log(23.0)*5.0;
	pos2 = pos1 + 0.1;
	glVertex3f(pos1,0.0,0.0);
	glVertex3f(pos2,0.0,0.0);
	glVertex3f(pos2,0.0,2.0);
	glVertex3f(pos1,0.0,2.0);
    
    
    float sample_of_c = 524.0*((float)(WINDOW_SIZE*FRAME_SIZE)/44100.0);
    pos1 = (float)log(sample_of_c)*5.0;
//    cout << sample_of_c << endl;
	pos2 = pos1 + 0.1;
	glVertex3f(pos1,0.0,0.0);
	glVertex3f(pos2,0.0,0.0);
	glVertex3f(pos2,0.0,2.0);
	glVertex3f(pos1,0.0,2.0);
    
    glEnd();
    
    
    float bins[BINS];
    float bin_size = log(WINDOW_SIZE*FRAME_SIZE) / 10.0 ;
    for ( int i = 0 ; i < BINS ; i++ ) {
    	bins[i] = 0;
    }
    
    
    for ( int i = 0 ; i < WINDOW_SIZE*FRAME_SIZE;  i++ ) {
    	pos1 = (float)log((double)i+1);
    	bins[(int)(pos1/bin_size)] += abs(fftw_out[i][0]) + fftw_out[i][0] ; 	
    }
    
    glColor3f(0.8,0.2,0.3);
    glPushMatrix();
    glTranslatef(0.0,3.0,3.0);
    /*glBegin(GL_QUADS);
    	for ( int i = 0 ; i < BINS ; i++ ) {
    		glVertex3f(i*bin_size*5.0,0.0,0.0);
    		glVertex3f((i+1)*bin_size*5.0,0.0,0.0);
    		glVertex3f((i+1)*bin_size*5.0,0.0,bins[i]);
    		glVertex3f(i*bin_size*5.0,0.0,bins[i]);
    	}
    glEnd();*/
    glPopMatrix();

    //display the model
    //mymodel->display();
    //mytorus->display();

	

    glPopMatrix();

    SDL_GL_SwapBuffers( );
}

void CEngine::setup_opengl( int width, int height )
{
    float ratio = (float) width / (float) height;

    /* Our shading model--Gouraud (smooth). */
        glShadeModel( GL_SMOOTH );

    /* Culling. */
    //    glCullFace( GL_BACK );
    //glFrontFace( GL_CCW );
    //glEnable( GL_CULL_FACE );
   // glEnable( GL_DEPTH_TEST );
    //glEnable( GL_LIGHTING );
    //glEnable( GL_TEXTURE_2D );
    //glEnable( GL_LIGHT0 ); 
	
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ; 


    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );

    mycamera->set_projection();
}




CEngine::CEngine( int argc, char* argv[] )
{
    /* Information about the current video settings. */
    const SDL_VideoInfo* info = NULL;
    /* Dimensions of our window. */
    int width = 0;
    int height = 0;
    int bpp = 0;
    int flags = 0;
    string model_name ;

    /*    if ( argc > 1 ) {
	model_name =  argv[1];
    } else {
	cout << "No model specified." << endl ;
	exit(1);
    }


    cout << "Model: " << model_name << endl ; 
    mymodel = new CModel(model_name);
    mymodel->read();*/

    //mytorus = new CTtorus();

    
    mycamera = new Ccamera();

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf( stderr, "Video initialization failed: %s\n",
             SDL_GetError( ) );
        quit( 1 );
    }

    info = SDL_GetVideoInfo( );

    if( !info ) {
        fprintf( stderr, "Video query failed: %s\n",
             SDL_GetError( ) );
        quit( 1 );
    }
    
    width = 800;
    height = 600;
    mycamera->set_aspect(width, height);
    bpp = info->vfmt->BitsPerPixel;
    
    /*    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );*/
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

//    flags = SDL_OPENGL | SDL_FULLSCREEN; 
    flags = SDL_OPENGL;
   
    SDL_ShowCursor(SDL_DISABLE);	

    if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) {
  
        fprintf( stderr, "Video mode set failed: %s\n",
             SDL_GetError( ) );
        quit( 1 );
    }

    setup_opengl( width, height );
    
    //mytorus->initialise();
}

void CEngine::start(){
    last_tick_count = SDL_GetTicks(); 
    while( 1 ) {
		current_tick_count = SDL_GetTicks();
		diff_ticks = current_tick_count - last_tick_count; 
		
		if ( diff_ticks > 1000 / FPS  ) {
				last_tick_count = current_tick_count; 	
				/* Process incoming events. */
				process_events( );
				/* Draw the screen. */
				draw_screen( );
		}
	}
}
