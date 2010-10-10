/*
* Name: CModel.cpp
* Author: Niall Moran
* License: GPL
* Desc: Implentation file for CModel class. The class contains functionality to 
* parse and display wavefront .obj CModel files. 
*
*/

#include "model.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void CModel::read(){
	ifstream input, input2; 
	int vertex = 0 , normal = 0, face = 0 ;

	if ( name != "" ) {
		string line;

		//construct filename of CModel file from CModel name.
		string filename = "models/" + name + ".obj"; 

		//attempt to open CModel file.
		input.open(filename.c_str());

		if ( input.is_open() ){
			//Read through CModel file and count how many vertices, normals and faces it contains.
			while ( ! input.eof() ){
				getline( input, line ) ; //read line
				if ( line.find("v ", 0)  != string::npos ) {
					vertex++; 
				} else if ( line.find("vn", 0)  != string::npos ) {
					normal++; 
				} else if ( line.find("vt", 0)  != string::npos ) {
					text_count++; 
				} else if ( line.find("f ", 0)  != string::npos ) {
					face++; 
				}
			}
			input.close();

			//allocate memory to store vertices, faces and normals.
	   		vertices = new float[vertex*3];
			faces = new int[face*3];

			if ( normal > 0 )  {
				face_normals = new int[face*3];
				normals = new float[normal*3];
			}
			if ( text_count > 0 )  {
				face_textures = new int[face*3];
				texture_coords = new float[text_count*3];
			}

			if ( vertices == NULL || faces == NULL || normals == NULL ) 
			{				
				cerr << "Error allocating memory for CModel " << name << endl ; 
				exit(1);
			}

			input.open(filename.c_str());
			input2.open(filename.c_str());

			int vertex_i = 0;
			int face_i = 0;
			int normal_i = 0;
			int text_i = 0;
		
			//Loop through file again and this time populate vertex, normal and face arrays.
			while ( ! input2.eof() ){
				getline( input2, line ) ; //read line
				//if the line contains a vertex
				if ( line.find("v ", 0)  != string::npos ) 
				{
					int last_space_pos = line.find(" ", 0 ) ;
					for ( int i = 0 ; i < 3 ; i++ ) 
					{
						vertices[vertex_i++] = atof((line.substr(last_space_pos, line.find(" " , last_space_pos + 1))).c_str()); 
						last_space_pos = line.find(" ", last_space_pos + 1 ) ;
					} //end for
				//if the line contains a vertex normal
				} else if ( line.find("vn", 0)  != string::npos ) 
				{
					int last_space_pos = line.find(" ", 0 ) ;
					for ( int i = 0 ; i < 3 ; i++ ) 
					{
						normals[normal_i++] = atof((line.substr(last_space_pos, line.find(" " , last_space_pos + 1))).c_str()); 
						last_space_pos = line.find(" ", last_space_pos + 1 ) ;
					} //end for 
				//if the line contains a face
				}  else if ( line.find("vt", 0)  != string::npos ) 
				{
					int last_space_pos = line.find(" ", 0 ) ;
					for ( int i = 0 ; i < 3 ; i++ ) 
					{
						texture_coords[text_i++] = atof((line.substr(last_space_pos, line.find(" " , last_space_pos + 1))).c_str()); 
						last_space_pos = line.find(" ", last_space_pos + 1 ) ;
					} //end for 
				//if the line contains a face
				} else if ( line.find("f ", 0)  != string::npos ) 
				{
					int last_space_pos = line.find(" ", 0 ) ;
					for ( int i = 0 ; i < 3 ; i++ ) 
					{
						string buf = line.substr(last_space_pos, line.find(" " , last_space_pos + 1));
						faces[face_i] = atoi(buf.substr(0, buf.find("//", 0)).c_str()); 
						faces[face_i]--; 
						face_normals[face_i] = atoi(buf.substr(buf.find("//", 0) + 2 , buf.length() -1 ).c_str()); 
						face_normals[face_i++]--; 
						last_space_pos = line.find(" ", last_space_pos + 1 ) ;
					} //end for
				} // end if else statment
			} //end while loop
			input2.close();
		} else  {


			
			cout << "File not open." << endl;

		}

		/*
		//print out vertices, normals and faces for debugging purposes.
		cout << "Vertices: " << vertex << endl ;
		for ( int i = 0 ; i < vertex  ; i ++  ) {
			cout << i << ": " << vertices[i*3] << ", " << vertices[i*3 +1] << ", " << vertices[i*3+2] << endl ;
		} 

		cout << "Normals: " << normal << endl ;
		for ( int i = 0 ; i < normal  ; i ++  ) {
			cout << i << ": " << normals[i*3] << ", " << normals[i*3 +1] << ", " << normals[i*3+2] << endl ;
		} 

		cout << "Faces: " << face << endl ;
		for ( int i = 0 ; i < face  ; i ++  ) {
			cout << i << ": " << faces[i*3] << "/" << face_normals[i*3] << ", " << faces[i*3 +1] << "/" << face_normals[i*3+1] << ", " << faces[i*3+2] << "/" << face_normals[i*3+2] << endl ;
		} */


		vertex_count = vertex;
		face_count = face;
		normal_count = normal;
	} //end if name != ""

}//end function read

void CModel::compile() {

	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	
	glColor3f(1.0, 1.0,1.0 ) ;
	glBegin(GL_TRIANGLES);
		for ( int i = 0 ; i < face_count * 3 ; i++ ) {
			glNormal3fv(&normals[face_normals[i]*3]);
			glVertex3fv(&vertices[faces[i]*3]);
		}

	glEnd();

	glEndList();
	compiled = true;
}

void CModel::display(){

	if ( !compiled ) {
		compile();
	} 

	glCallList(display_list);

/*	glEnableClientState(GL_VERTEX_ARRAY);
    	glVertexPointer(3, GL_FLOAT, 0, vertices);

	//glEnableClientState(GL_NORMAL_ARRAY);
    	//glNormalPointer(GL_FLOAT, 0, normals);

	glColor3f(1.0,1.0,1.0);

    	glDrawElements(GL_TRIANGLES, face_count * 3 ,  GL_UNSIGNED_INT , faces );*/
}

CModel::~CModel(){
	delete []vertices;
	delete []faces;
	delete []face_normals;
	delete []normals;
}
