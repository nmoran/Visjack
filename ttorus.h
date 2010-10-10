/*
*
* Name: ttorus.h
* Author: Niall Moran
* License: GPL
* Desc: Header file for model class. The class contains functionality to 
* parse and display wavefront .obj model files.
*
*/


#ifndef _TTORUS_H_
#define _TTORUS_H_

#include <string>

#include "util.h"

using namespace std;

class CTtorus {
	private:
	float *vertices;
	int *faces;
	int *face_normals;
	int *face_textures;
	float *normals;
	float *texture_coords;
	string name;
	int vertex_count;
	int face_count;
	int normal_count;
	int text_count;
	bool compiled;
	GLuint display_list;
	GLuint texture[2];

	public:
	/*
	* Constructor that takes name of model as argument.
 	*
	* @parm a_name Name of model to read. Model file will be name wiht .obj appended.
	*/
	CTtorus( string a_name ) {
		name = a_name;
		vertex_count = 0;
		face_count = 0;
		normal_count = 0;
		text_count = 0;
		compiled = false;
	}

	/*
	* Null Constructor simply sets name to ""
	*/
	CTtorus( ) {
		CTtorus("");
	}

	void initialise();

	/* 
	* This method renders the model.
	*/
	void display (); 

	~CTtorus();
};


#endif
