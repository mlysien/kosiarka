#pragma once

class Mapa
{
private:
//DANE SK�ADOWE
	
	//szeroko�� mapy
	int Mwidth;

	//wysoko�� mapy
	int Mheight;

public:
//DANE SK�ADOWE

	//liczby odpowiadaj�ce teksturom mapy
	
	//trawa
	int Grass;
	
	//kamie�
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

//FUNKCJE SK�ADOWE

	//kosntruktor
	Mapa();

	//funkcja �aduje map� z pliku .txt
	bool LoadMap(const char *plik);

};
