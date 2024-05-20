#pragma once

class Scena{
public:
//DANE SK�ADOWE

	//g��wna powierzchnia ekranu
	SDL_Surface *EKRAN;

	SDL_Surface *texture;

//FUNKCJE  SK�ADOWE

	//konstruktor
	Scena();

	//funkcja uruchamiaj�ca tryb graficzny
	bool RunSDL(int ScrWidth, int ScrHeight, int BPP, 
				const char *WinTittle, bool FullScr);

	//funkcja �aduj�ca bitmapy (zoptymalizowane)
	SDL_Surface *LoadSprite(const char *plik);

	//funkcja wy�wietla bitmape na ekranie
	void ShowSprite(int x, int y, SDL_Surface* skad, 
								  SDL_Surface* gdzie);
};
