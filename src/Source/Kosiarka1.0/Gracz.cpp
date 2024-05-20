#include<SDL.h>
#include<SDL_image.h>
#include "Gracz.h"


Gracz::Gracz(){
//kostruktor
	pozX= 0;
	pozY= 0;
	velocity= 0.0;

	sqGracz.x= pozX;
	sqGracz.y= pozY;
	sqGracz.h= 32;
	sqGracz.w= 32;

	txGracz= 0;
}