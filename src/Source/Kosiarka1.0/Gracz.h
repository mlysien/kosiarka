#pragma once

class Gracz{
public:
//DANE SK�ADOWE

	//pozycja gracza na oX
	int pozX;
	
	//pozycja gracza na oY
	int pozY;

	//pr�dko�� gracza(zale�na od fps'�w
	float velocity;
	
	//kafelka gracza
	SDL_Rect sqGracz;

	//tekstura gracza
	SDL_Surface *txGracz;

//FUNKCJE SK�ADOWE

	//konstruktor
	Gracz();
};