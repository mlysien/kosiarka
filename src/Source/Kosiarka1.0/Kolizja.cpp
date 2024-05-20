#include<SDL.h>
#include<SDL_image.h>
#include "Gracz.h"
#include "Kolizja.h"
#include "Scena.h"

Gracz gracz;

bool Kolizja::CheckBorder(){

	if(gracz.pozX>640){

		return true;

	}
	if(gracz.pozX<0){

		return true;

	}
}