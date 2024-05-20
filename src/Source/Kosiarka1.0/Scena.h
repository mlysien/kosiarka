#pragma once

class Scena{
public:
//DANE SK£ADOWE

	//g³ówna powierzchnia ekranu
	SDL_Surface *EKRAN;

	SDL_Surface *texture;

//FUNKCJE  SK£ADOWE

	//konstruktor
	Scena();

	//funkcja uruchamiaj¹ca tryb graficzny
	bool RunSDL(int ScrWidth, int ScrHeight, int BPP, 
				const char *WinTittle, bool FullScr);

	//funkcja ³aduj¹ca bitmapy (zoptymalizowane)
	SDL_Surface *LoadSprite(const char *plik);

	//funkcja wyœwietla bitmape na ekranie
	void ShowSprite(int x, int y, SDL_Surface* skad, 
								  SDL_Surface* gdzie);
};
