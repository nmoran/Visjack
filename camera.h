#ifndef _CAMERA_H_ 
#define _CAMERA_H_ 

#include "util.h"


class Ccamera {
private :
	VECTOR position ;
	VECTOR direction ;
	VECTOR view_direction ;
	VECTOR cross_direction ;
	VECTOR up_direction ;
	float xaxis_angle;
	float zaxis_angle; 
	int width , height ;
	float near_view , far_view;
	float mouse_sensitivity ; 
	float strafe;
	float move_forward_back; 
	float move_up_down;
	float movement_speed ;

public :
	Ccamera();
	void set_projection();
	void set_modelview();
	void set_aspect(int w , int h );
	void set_position(VECTOR *position);
	void translate(VECTOR *amount);
	void move_forward(float amount);
	void move_back(float amount);
	void strafe_left(float amount);
	void strafe_right(float amount);
	void look_up_down(float amount);
	void look_left_right(float amount);
	void advance_camera(float amount);
	void evaluate_directions();
	void stop_strafe();
	void stop_move_forward_back();
	void move_up(float amount);
	void move_down(float amount);
	void stop_up_down();
	
};


#endif
