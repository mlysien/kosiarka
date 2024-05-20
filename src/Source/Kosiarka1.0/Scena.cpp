#include<SDL.h>
#include<SDL_image.h>
#include "Scena.h"

//konstruktor
Scena::Scena(){

	EKRAN = NULL;

	texture= NULL;
}


//inicjalizacja SDL'a
bool Scena::RunSDL(int ScrWidth, int ScrHeight, int BPP, 
				   const char *WinTittle, bool FullScr){
	

	if( SDL_Init(SDL_INIT_EVERYTHING)== -1){
    	return false;
	}
	//wy³¹czenie kursora
	SDL_ShowCursor( SDL_DISABLE );

	//za³adowanie powierzchni
(FullScr) 
? EKRAN= SDL_SetVideoMode( ScrWidth, ScrHeight, BPP, SDL_SWSURFACE								| SDL_FULLSCREEN )
: EKRAN= SDL_SetVideoMode(ScrWidth, ScrHeight, BPP, SDL_SWSURFACE );

	if(EKRAN== 0){
		return false;
	}
	
	//Ikona
	SDL_Surface* icon = SDL_LoadBMP("mower.ico");
	SDL_WM_SetIcon(icon, NULL);
	//ustawienie tytu³u okienka
	SDL_WM_SetCaption(WinTittle, 0);

	//je¿eli wszystko posz³o wporz¹dku
	return true;
}


//funkcja ³aduje bitmapy i je optymalizuje
SDL_Surface *Scena::LoadSprite(const char *plik){

	//tymczasowa za³adowana bitmapa
	SDL_Surface *zaladowaneBMP= 0;

	//tutaj znajdowaæ siê bêdzie poprawiona bitmapa
	SDL_Surface *poprawioneBMP= 0;

	//za³adowanie tymczasowej bitmapy
	zaladowaneBMP= SDL_LoadBMP(plik);

	if(zaladowaneBMP!= 0){
	
		//stworzenie zoptymalizowanej bitmapy
		poprawioneBMP= SDL_DisplayFormat(zaladowaneBMP);

		if(poprawioneBMP!= 0){
			Uint32 colorkey= SDL_MapRGB( poprawioneBMP->format, 
									0xFF, 0xFF, 0xFF );
		
			SDL_SetColorKey(poprawioneBMP, SDL_SRCCOLORKEY,										colorkey);

		}


		//zwolnienie pamiêci spod starej bitmapy
		SDL_FreeSurface(zaladowaneBMP);

	}

	//zwrócenie poprawionej bitmapy
	return poprawioneBMP;
}


//funkcja wyœwietla sprity na ekranie
void Scena::ShowSprite(int x, int y, SDL_Surface* skad, 
				SDL_Surface* gdzie){

	//tymczasowy obszar
	SDL_Rect square;

	square.x= x;
	square.y= y;
	square.h=32;
	square.w=32;

	//Blit powierzchni
	SDL_BlitSurface(skad, 0, gdzie, &square);

}


