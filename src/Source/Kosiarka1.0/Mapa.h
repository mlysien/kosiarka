#pragma once

class Mapa
{
private:
//DANE SK£ADOWE
	
	//szerokoœæ mapy
	int Mwidth;

	//wysokoœæ mapy
	int Mheight;

public:
//DANE SK£ADOWE

	//liczby odpowiadaj¹ce teksturom mapy
	
	//trawa
	int Grass;
	
	//kamieñ
	int Stone;

	//gracz
	int Player;

	//woda
	int Water;

	//kwiatek
	int Flower;

	//parking/podjazd
	int Parking;



	//tablica do przechowywania struktury mapy
	int Map[15][20];

//FUNKCJE SK£ADOWE

	//kosntruktor
	Mapa();

	//funkcja ³aduje mapê z pliku .txt
	bool LoadMap(const char *plik);

};
