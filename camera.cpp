#include "camera.h"

void Ccamera::set_projection()
{
    	glViewport( 0, 0, width, height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective ( 65.0 , (GLfloat) width/(GLfloat)height ,near_view ,far_view );
	glMatrixMode(GL_MODELVIEW);
}

void Ccamera::set_modelview()
{
	gluLookAt(position.x , position.y , position.z , 
	      view_direction.x + position.x  ,view_direction.y + position.y ,view_direction.z + position.z ,
		  up_direction.x , up_direction.y  , up_direction.z ); 
}

Ccamera::Ccamera()
{
	position.set(30.0,-50.0, 0.0);
	direction.set(0.0,1.0,0.0);
	view_direction.set(0.0,1.0,0.0);
	cross_direction.set(1.0,0.0,0.0);
	up_direction.set(0.0,0.0,1.0);
	near_view = 1.0 ;
	far_view = 500.0;
	xaxis_angle = 0.0;
	zaxis_angle = 0.0;
	mouse_sensitivity = 50.0;
	strafe = 0.0;
	move_forward_back = 0.0; 
	move_up_down = 0.0;
	movement_speed = 5.0;
}

void Ccamera::set_aspect(int w , int h )
{
	width = w;
	height = h;
}

void Ccamera::translate(VECTOR *amount ) {
	position = position + *amount; 
}

void Ccamera::move_forward(float amount){
	//position = position + direction * amount ; 	
	move_forward_back = amount; 
}

void Ccamera::move_up(float amount){
	//position = position + direction * amount ; 	
	move_up_down = amount; 
}

void Ccamera::move_down(float amount){
	//position = poition + direction * amount ; 	
	move_up_down = -amount; 
}

void Ccamera::stop_up_down(){
	move_up_down = 0.0; 
}


void Ccamera::move_back(float amount){
	//position = position + direction * (-amount) ; 	
	move_forward_back = -amount; 
}

void Ccamera::strafe_left(float amount){
	//position = position + cross_direction * (-amount) ; 	
	strafe = -amount;
}

void Ccamera::strafe_right(float amount){
	//position = position + cross_direction * (amount) ; 	
	strafe = amount ;
}

void Ccamera::stop_move_forward_back(){
	move_forward_back = 0.0; 
}

void Ccamera::stop_strafe(){
	strafe = 0.0; 
}


void Ccamera::look_up_down ( float amount ) {
	xaxis_angle += amount * mouse_sensitivity ;
	if ( xaxis_angle > 90.0 ) 
		xaxis_angle = 90.0; 
	else  if ( xaxis_angle < -90.0 ) 
		xaxis_angle = -90.0; 

	evaluate_directions();
}

void Ccamera::look_left_right ( float amount ) {
	zaxis_angle += -amount * mouse_sensitivity ;
	if ( zaxis_angle >= 360.0 ) 
		zaxis_angle -= 360.0; 
	else  if ( zaxis_angle <= 0.0 ) 
		zaxis_angle += 360.0; 

	evaluate_directions();
}

void Ccamera::evaluate_directions() {
	//cout << zaxis_angle << " " << xaxis_angle << endl ; 
	float zcos = cos(zaxis_angle * PI / 180.0 ) ;
	float zsin = sin(zaxis_angle * PI / 180.0 ) ;
	float xcos = cos(xaxis_angle * PI / 180.0 ) ;
	float xsin = sin(xaxis_angle * PI / 180.0 ) ;

	view_direction.x = 0.0 ;  
	view_direction.y = xcos;
	view_direction.z = -xsin ;

	view_direction.x = zsin * view_direction.y ; 
	view_direction.y = zcos * view_direction.y ;
	view_direction.z = view_direction.z ; 

	direction.x =  zsin ;
	direction.y =  zcos ;
	direction.z = direction.z ; 

	cross_direction.x = zcos; 
	cross_direction.y = -zsin; 
}

void Ccamera::advance_camera(float amount){
       
	position = position + cross_direction * strafe * amount * movement_speed ; 	
	position = position + direction * move_forward_back * amount * movement_speed ;  	
	position = position + up_direction * move_up_down * amount;
}
