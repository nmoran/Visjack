/*
*
* Name: model.h
* Author: Niall Moran
* License: GPL
* Desc: Header file for model class. The class contains functionality to 
* parse and display wavefront .obj model files.
*
*/


#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include "util.h"

using namespace std;

class CModel {
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

	public:
	/*
	* Constructor that takes name of model as argument.
 	*
	* @parm a_name Name of model to read. Model file will be name wiht .obj appended.
	*/
	CModel( string a_name ) {
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
	CModel( ) {
		CModel("");
	}

	/*
	* This method opens the model file and parses it.
	*/
	void read(); 

	/* 
	* This method renders the model.
	*/
	void display (); 

	/* 
	* this method compiles a display list for the model 
	*/
	void compile (); 


	void get_geom(float *geoms ); 

	~CModel();
};


#endif
