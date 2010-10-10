/*
* Name: CModel.cpp
* Author: Niall Moran
* License: GPL
* Desc: Implentation file for CModel class. The class contains functionality to 
* parse and display wavefront .obj CModel files. 
*
*/

#include "ttorus.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void CTtorus::display(){

 // select our current texture
  

  glColor3f(1.0,1.0,1.0);
  
  glBindTexture( GL_TEXTURE_2D, this->texture[0] );

  glBegin(GL_QUADS);
  glTexCoord2i( 0, 0 );
  glVertex3f(0.0,0.0,1.0);
  glTexCoord2i( 0, 1 );
  glVertex3f(0.0,0.0,0.0);
  glTexCoord2i( 1, 1 );
  glVertex3f(1.0,0.0,0.0);
  glTexCoord2i( 1, 0 );
  glVertex3f(1.0,0.0,1.0);
  glEnd();

  glPushMatrix();
  
  glTranslatef(4.0,0.0,0.0);

  glBegin(GL_QUADS);
  glTexCoord2i( 0, 0 );
  glVertex3f(1.0,0.0,0.0);
  glTexCoord2i( 1, 0 );
  glVertex3f(1.0,0.0,1.0);
  glTexCoord2i( 1, 1 );
  glVertex3f(0.0,0.0,1.0);
  glTexCoord2i( 0, 1 );
  glVertex3f(0.0,0.0,0.0);
  glEnd();
  
  glPopMatrix();

/*	glEnableClientState(GL_VERTEX_ARRAY);
    	glVertexPointer(3, GL_FLOAT, 0, vertices);

	//glEnableClientState(GL_NORMAL_ARRAY);
    	//glNormalPointer(GL_FLOAT, 0, normals);

	glColor3f(1.0,1.0,1.0);

    	glDrawElements(GL_TRIANGLES, face_count * 3 ,  GL_UNSIGNED_INT , faces );*/
}

void CTtorus::initialise() {

  GLenum texture_format;
  GLint  nOfColors;
  


  // load sample.png into image
  SDL_Surface *image;
  image=IMG_Load("sample.bmp");
  
  //image = SDL_LoadBMP( "bumps.bmp" ) ;
  if(!image) {
    printf("IMG_Load: %s\n", IMG_GetError());
    // handle error
  }


  // get the number of channels in the SDL surface
        nOfColors = image->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (image->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (image->format->Rmask == 0x000000ff) {
                        texture_format = GL_RGB;
                    	printf("Format is RGB\n");
                } else {
                        texture_format = GL_BGR;
                        printf("Format is BGR\n");
                }
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }

	printf("Image details: width %d, height %d\n", image->w, image->h);
	printf("No. of colours: %d\n", nOfColors);
 

  // allocate a texture name
  glGenTextures( 1, &this->texture[0] );
  // select our current texture
  glBindTexture( GL_TEXTURE_2D, this->texture[0] );

  // select modulate to mix texture with color for shading
  //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  // when texture area is small, bilinear filter the closest mipmap
  //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
  //               GL_LINEAR_MIPMAP_NEAREST );
  // when texture area is large, bilinear filter the original
  //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  // the texture wraps over at the edges (repeat)
  //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  glTexImage2D( GL_TEXTURE_2D, 0, nOfColors , image->w, image->h, 0,
                      GL_BGR, GL_UNSIGNED_BYTE, image->pixels );

}


CTtorus::~CTtorus(){
}
